//
// Created by horacio on 9/19/16.
//

#ifndef TP1_CLIENTE_H
#define TP1_CLIENTE_H


#include "Proceso.h"
#include <iostream>
#include <string>
#include <sys/types.h> 
#include "../Logger.h"
#include "../Estructuras/Semaforo.h"
#include "../Estructuras/IDSemaforos.h"
#include "../Estructuras/FifoLectura.h"
#include "../Constantes.h"
#include "../Mesas.h"

class Cliente : public Proceso {

private:
    int id;
    int plata;
    Semaforo sem_entrada;
    Semaforo sem_recepcion;
    Semaforo sem_living;
    FifoLectura fifoRecepcionLectura;
    FifoLectura fifoLivingLectura;
    int mesaAsignada;

public:
    Cliente(int id, Semaforo sem_entrada, Semaforo sem_recepcion,Semaforo sem_living,FifoLectura fifoRecepcionLectura,FifoLectura fifoLivingLectura);

private:

    void _run();
    void esperarMesa();
    void pedirPlatos();
    void esperarEnElLiving();
};


#endif //TP1_CLIENTE_H
