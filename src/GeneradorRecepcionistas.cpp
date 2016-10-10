#include "GeneradorRecepcionistas.h"
#include "Procesos/RecepcionLiving.h"

GeneradorRecepcionistas::GeneradorRecepcionistas(int cantidadDeRecepcionistas,FifoEscritura fifoRecepcionEscritura,FifoEscritura fifoLivingEscritura)
        :fifoRecepcionEscritura(fifoRecepcionEscritura),
         fifoLivingEscritura(fifoLivingEscritura){

    this->cantidadRecepcionistas = cantidadDeRecepcionistas;

}

pid_t GeneradorRecepcionistas::cargarRecepcionistas(Semaforo sem_entrada,Semaforo sem_recepcion,Semaforo sem_living,int cantidadDeMesas) {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador recepcionistas");

    }

    if (pid == 0) {

        fifoRecepcionEscritura.abrir();
        fifoLivingEscritura.abrir();

        for( int i = 0 ; i < cantidadRecepcionistas ; i++){

            Recepcionista recepcionista(std::to_string(i), sem_entrada, sem_recepcion,fifoRecepcionEscritura,cantidadDeMesas);
            recepcionista.run();

        }

        RecepcionLiving recepcionistaLiving(sem_living,fifoLivingEscritura,cantidadDeMesas);
        recepcionistaLiving.run();

        for (int i = 0; i <= cantidadRecepcionistas; ++i) {

            wait(NULL);

        }

        fifoRecepcionEscritura.cerrar();
        fifoLivingEscritura.cerrar();

        exit(0);

    } else {
        return pid;
    }

}
