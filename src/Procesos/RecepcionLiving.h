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

public:

    RecepcionLiving(Semaforo sem_living,FifoEscritura fifoLivingEscritura,int cantidadDeMesas);

private:
    Semaforo sem_living;
    FifoEscritura fifoLivingEscritura;
    int cantidadDeMesas;

    void _run();

};


#endif //TP1_RECEPCIONLIVING_H
