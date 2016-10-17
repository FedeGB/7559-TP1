//
// Created by mariano on 17/10/16.
//

#include "GeneradorDeCocinero.h"
#include "Logger.h"


GeneradorDeCocinero::GeneradorDeCocinero() {
    this->existioCorteDeLuz = false;
    this->cortesDeLuz = 0;
}

pid_t GeneradorDeCocinero::cargarCocinero() {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador cocinero");

    }

    if (pid == 0) {

        this->sigint_handler->setAtenderSignal(this);

        fifoMozosCocineroEscritura->abrir();
        fifoCocineroLectura->abrir();

        Cocinero cocinero;
        this->configurarCocinero(cocinero);
        pidCocinero = cocinero.run();

        Logger::getInstance().log("CREADO COCINERO CON PID "+std::to_string(pidCocinero));

        wait(NULL);

        while( this->existioCorteDeLuz ) {

            wait(NULL);

            this->existioCorteDeLuz = false;

            sem_espera_luz->p();

            this->crearCocineroDespuesDelCorte();

            wait(NULL);

        }

        fifoMozosCocineroEscritura->cerrar();
        fifoCocineroLectura->cerrar();

        exit(0);

    } else {

        return pid;

    }


}

void GeneradorDeCocinero::setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura) {
    GeneradorDeCocinero::fifoMozosCocineroEscritura = fifoMozosCocineroEscritura;
}

void GeneradorDeCocinero::setFifoCocineroLectura(FifoLectura *fifoCocineroLectura) {
    GeneradorDeCocinero::fifoCocineroLectura = fifoCocineroLectura;
}

void GeneradorDeCocinero::setMenu(Menu *menu) {
    GeneradorDeCocinero::menu = menu;
}

void GeneradorDeCocinero::setSigint_handler(SIGINT_Handler *sigint_handler) {
    GeneradorDeCocinero::sigint_handler = sigint_handler;
}

void GeneradorDeCocinero::configurarCocinero(Cocinero &cocinero) {

    cocinero.setFifoCocineroLectura(fifoCocineroLectura);
    cocinero.setFifoMozosCocineroEscritura(fifoMozosCocineroEscritura);
    cocinero.setMenu(menu);
    cocinero.setSigint_handler(sigint_handler);

}

void GeneradorDeCocinero::crearCocineroDespuesDelCorte() {

    Cocinero cocinero(this->cortesDeLuz);
    this->configurarCocinero(cocinero);
    pidCocinero = cocinero.run();

}

void GeneradorDeCocinero::atenderSenial() {

    this->existioCorteDeLuz = true;
    this->cortesDeLuz++;

    Logger::getInstance().log("CORTE DE LUZ COCINERO "+std::to_string(pidCocinero));

    kill(pidCocinero,CORTE_DE_LUZ);

}

void GeneradorDeCocinero::setSem_espera_luz(Semaforo *sem_espera_luz) {
    GeneradorDeCocinero::sem_espera_luz = sem_espera_luz;
}
