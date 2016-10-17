#include "GeneradorRecepcionistas.h"

GeneradorRecepcionistas::GeneradorRecepcionistas(){

}

void GeneradorRecepcionistas::setCantidadDeRecepcionistas(int cantidadDeRecepcionistas) {

    this->cantidadRecepcionistas = cantidadDeRecepcionistas;

}


pid_t GeneradorRecepcionistas::cargarRecepcionistas(int cantidadDeMesas) {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador recepcionistas");

    }

    if (pid == 0) {

        fifoRecepcionEscritura->abrir();
        fifoLivingEscritura->abrir();

        for( int i = 0 ; i < cantidadRecepcionistas ; i++){

            Recepcionista recepcionista(std::to_string(i),cantidadDeMesas);
            this->cargarRecepcionista(recepcionista);
            pid_t pidRecepcionista = recepcionista.run();

            canal.escribir(&pidRecepcionista,sizeof(pid_t));

        }

        canal.cerrar();

        RecepcionLiving recepcionistaLiving(cantidadDeMesas);
        this->cargarRecepcionistaLiving(recepcionistaLiving);
        recepcionistaLiving.run();

        for (int i = 0; i <= cantidadRecepcionistas; ++i) {

            wait(NULL);

        }

        fifoRecepcionEscritura->cerrar();
        fifoLivingEscritura->cerrar();

        exit(0);

    } else {
        return pid;
    }

}

void GeneradorRecepcionistas::setFifoRecepcionEscritura(FifoEscritura *fifoRecepcionEscritura) {
    GeneradorRecepcionistas::fifoRecepcionEscritura = fifoRecepcionEscritura;
}

void GeneradorRecepcionistas::setFifoLivingEscritura(FifoEscritura *fifoLivingEscritura) {
    GeneradorRecepcionistas::fifoLivingEscritura = fifoLivingEscritura;
}

void GeneradorRecepcionistas::setSem_entrada(Semaforo *sem_entrada) {
    GeneradorRecepcionistas::sem_entrada = sem_entrada;
}

void GeneradorRecepcionistas::setSem_recepcion(Semaforo *sem_recepcion) {
    GeneradorRecepcionistas::sem_recepcion = sem_recepcion;
}

void GeneradorRecepcionistas::setSem_living(Semaforo *sem_living) {
    GeneradorRecepcionistas::sem_living = sem_living;
}

void GeneradorRecepcionistas::cargarRecepcionista(Recepcionista &recepcionista) {

    recepcionista.setSem_entrada(sem_entrada);
    recepcionista.setSem_recepcion(sem_recepcion);
    recepcionista.setFifoRecepcionEscritura(fifoRecepcionEscritura);
    recepcionista.setSigint_handler(sigint_handler);
    recepcionista.setSem_espera_luz(sem_espera_luz);

}

void GeneradorRecepcionistas::cargarRecepcionistaLiving(RecepcionLiving &recepcionistaLiving) {

    recepcionistaLiving.setSem_living(sem_living);
    recepcionistaLiving.setFifoLivingEscritura(fifoLivingEscritura);

}

std::vector<pid_t> GeneradorRecepcionistas::getPidRecepcionistas() {

    for (int i = 0; i < cantidadRecepcionistas; ++i) {

        pid_t pidRecepcionista;
        canal.leer(&pidRecepcionista,sizeof(pid_t));
        this->pidRecepcionistas.push_back(pidRecepcionista);

    }

    canal.cerrar();

    return pidRecepcionistas;

}

void GeneradorRecepcionistas::setSigint_handler(SIGINT_Handler *sigint_handler) {
    GeneradorRecepcionistas::sigint_handler = sigint_handler;
}

void GeneradorRecepcionistas::setSem_espera_luz(Semaforo *sem_espera_luz) {
    GeneradorRecepcionistas::sem_espera_luz = sem_espera_luz;
}

