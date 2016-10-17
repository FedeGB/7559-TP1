//
// Created by mafv on 12/10/16.
//

#include "GeneradorMozos.h"
#include "Estructuras/FifoEscritura.h"

GeneradorMozos::GeneradorMozos(int cantidadDeMozos) {
    this->cantidadDeMozos = cantidadDeMozos;
}


GeneradorMozos::GeneradorMozos() {
}

void GeneradorMozos::setCantidadDeMozos(int cantidadDeMozos) {
    this->cantidadDeMozos = cantidadDeMozos;
}

pid_t GeneradorMozos::cargarMozos() {

    this->existioCorteDeLuz = false;
    this->cortesDeLuz = 0;

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador mozos");

    }

    if (pid == 0) {


        this->sigint_handler->setAtenderSignal(this);

        fifoMozosLectura->abrir();
        fifoMozosCocineroLectura->abrir();
        fifoCocineroEscritura->abrir();

        this->crearMozos();

        this->esperarMozos();

        while( this->existioCorteDeLuz ) {

            wait(NULL);

            this->existioCorteDeLuz = false;

            this->sem_espera_luz->p();

            this->crearMozosDespuesDelCorte();

            this->esperarMozos();

        }

        fifoMozosLectura->cerrar();
        fifoMozosCocineroLectura->cerrar();
        fifoCocineroEscritura->cerrar();

        exit(0);

    } else {

        return pid;

    }

}


void GeneradorMozos::setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas) {
    GeneradorMozos::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void GeneradorMozos::setFifoMozosLectura(FifoLectura *fifoMozosLectura) {
    GeneradorMozos::fifoMozosLectura = fifoMozosLectura;
}

void GeneradorMozos::configurarMozos(Mozo &mozo) {

    mozo.setFifoPedidoMozo(fifoMozosLectura);
    mozo.setFifoMozosCocineroLectura(fifoMozosCocineroLectura);
    mozo.setFifoCocineroEscritura(fifoCocineroEscritura);
    mozo.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    mozo.setMenu(menu);
    mozo.setSemaforosSaldos(semaforosSaldos);

}

void GeneradorMozos::setFifoCocineroEscritura(FifoEscritura * f){
    this->fifoCocineroEscritura = f;
}

void GeneradorMozos::setFifoMozosCocineroLectura(FifoLectura *f) {
    this->fifoMozosCocineroLectura = f;
}

void GeneradorMozos::setMenu(Menu *menu) {
    GeneradorMozos::menu = menu;
}

void GeneradorMozos::setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos) {
    GeneradorMozos::semaforosSaldos = semaforosSaldos;
}


void GeneradorMozos::crearMozos() {

    for (int i = 0; i < cantidadDeMozos; ++i) {

        Mozo mozo(i);
        mozo.setSigint_handler(this->sigint_handler);
        this->configurarMozos(mozo);
        pid_t pidMozo = mozo.run();

        pidMozos.push_back(pidMozo);

    }

}

void GeneradorMozos::esperarMozos() {

    for (int i = 0; i < cantidadDeMozos; ++i) {

        wait(NULL);

    }

}

void GeneradorMozos::crearMozosDespuesDelCorte() {

    pidMozos.clear();

    for (int i = 0; i < cantidadDeMozos ; ++i) {

        Mozo mozo(i,cortesDeLuz);
        mozo.setSigint_handler(this->sigint_handler);
        this->configurarMozos(mozo);
        pid_t pidMozo = mozo.run();

        pidMozos.push_back(pidMozo);

    }

}

void GeneradorMozos::atenderSenial() {

    this->existioCorteDeLuz = true;
    this->cortesDeLuz++;

    for(auto pid_mozo : pidMozos ) {

        kill(pid_mozo,CORTE_DE_LUZ);

    }

}

void GeneradorMozos::setSigint_handler(SIGINT_Handler *sigint_handler) {
    this->sigint_handler = sigint_handler;

}

void GeneradorMozos::setSem_espera_luz(Semaforo *sem_espera_luz) {
    GeneradorMozos::sem_espera_luz = sem_espera_luz;
}


