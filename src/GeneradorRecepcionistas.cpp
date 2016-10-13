#include "GeneradorRecepcionistas.h"

GeneradorRecepcionistas::GeneradorRecepcionistas(int cantidadDeRecepcionistas){

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
            recepcionista.run();

        }

        RecepcionLiving recepcionistaLiving(cantidadDeMesas);
        this->cargarRecepcionistaLiving(recepcionistaLiving);
        recepcionistaLiving.run();

        for (int i = 0; i <= cantidadRecepcionistas; ++i) {

            wait(NULL);

        }

        fifoRecepcionEscritura->cerrar();
        fifoLivingEscritura->cerrar();

        delete fifoLivingEscritura;
        delete fifoRecepcionEscritura;
        delete sem_living;
        delete sem_recepcion;
        delete sem_entrada;

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

}

void GeneradorRecepcionistas::cargarRecepcionistaLiving(RecepcionLiving &recepcionistaLiving) {

    recepcionistaLiving.setSem_living(sem_living);
    recepcionistaLiving.setFifoLivingEscritura(fifoLivingEscritura);

}
