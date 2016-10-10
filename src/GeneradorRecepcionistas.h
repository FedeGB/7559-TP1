//
// Created by mafv on 09/10/16.
//

#ifndef TP1_GENERADORRECEPCIONISTAS_H
#define TP1_GENERADORRECEPCIONISTAS_H

#include "Estructuras/Semaforo.h"
#include "Procesos/Recepcionista.h"
#include "Estructuras/FifoEscritura.h"
#include "Constantes.h"

#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorRecepcionistas {

private:

    int cantidadRecepcionistas;
    FifoEscritura fifoRecepcionEscritura;
    FifoEscritura fifoLivingEscritura;

public:

    GeneradorRecepcionistas(int cantidadDeRecepcionistas,FifoEscritura fifoRecepcionEscritura,FifoEscritura fifoLivingEscritura);

    pid_t cargarRecepcionistas(Semaforo sem_entrada,Semaforo sem_recepcion,Semaforo sem_living,int cantidadDeMesas);

};


#endif //TP1_GENERADORRECEPCIONISTAS_H
