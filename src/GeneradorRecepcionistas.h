//
// Created by mafv on 09/10/16.
//

#ifndef TP1_GENERADORRECEPCIONISTAS_H
#define TP1_GENERADORRECEPCIONISTAS_H

#include "Estructuras/Semaforo.h"
#include "Procesos/Recepcionista.h"
#include "Estructuras/FifoEscritura.h"
#include "Constantes.h"
#include "Procesos/RecepcionLiving.h"
#include "Estructuras/Pipe.h"

#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorRecepcionistas {

private:

    Pipe canal;
    std::vector<pid_t> pidRecepcionistas;
    int cantidadRecepcionistas;
    FifoEscritura *fifoRecepcionEscritura;
    FifoEscritura *fifoLivingEscritura;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    Semaforo *sem_living;
public:

    GeneradorRecepcionistas();

    void setCantidadDeRecepcionistas(int cantidadDeRecepcionistas);

    pid_t cargarRecepcionistas(int cantidadDeMesas);

    void setFifoRecepcionEscritura(FifoEscritura *fifoRecepcionEscritura);

    void setFifoLivingEscritura(FifoEscritura *fifoLivingEscritura);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setSem_living(Semaforo *sem_living);

    std::vector<pid_t> getPidRecepcionistas();

private:

    void cargarRecepcionista(Recepcionista &recepcionista);
    void cargarRecepcionistaLiving(RecepcionLiving &recepcionistaLiving);

};


#endif //TP1_GENERADORRECEPCIONISTAS_H
