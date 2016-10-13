//
// Created by mafv on 10/10/16.
//

#ifndef TP1_RECEPCIONLIVING_H
#define TP1_RECEPCIONLIVING_H


#include "Proceso.h"
#include "../Estructuras/Semaforo.h"
#include "../Estructuras/FifoEscritura.h"
#include "../AdministradorLiving.h"

class RecepcionLiving : public Proceso {

private:
    int cantidadDeMesas;
    Semaforo *sem_living;
    FifoEscritura *fifoLivingEscritura;

public:

    RecepcionLiving(int cantidadDeMesas);

    void setSem_living(Semaforo *sem_living);

    void setFifoLivingEscritura(FifoEscritura *fifoLivingEscritura);

private:


    void _run();

};


#endif //TP1_RECEPCIONLIVING_H
