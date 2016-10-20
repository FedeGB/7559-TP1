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
#include "../Estructuras/FifoEscritura.h"
#include "../Menu.h"
#include "../AtenderSignal.h"
#include "SaldoDeMesa.h"

class Cliente : public Proceso, public AtenderSignal {

private:
    int id;
    int plata;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    Semaforo *sem_living;
    FifoLectura *fifoRecepcionLectura;
    FifoLectura *fifoLivingLectura;
    FifoEscritura *fifoMozosEscritura;
    int mesaAsignada;
    std::map<int,Semaforo> semaforosPedidoDeMesas;
    std::map<int, Semaforo> semaforosSaldos;
    Menu *menu;
    int platoPedidos;
    bool estoyDentro;
    int cortesDeLuz;

public:

    Cliente(int id);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setSem_living(Semaforo *sem_living);

    void setFifoRecepcionLectura(FifoLectura *fifoRecepcionLectura);

    void setFifoLivingLectura(FifoLectura *fifoLivingLectura);

    void setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas);

    void setMenu(Menu *menu);

    void setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos);

    void atenderSenial();


private:

    void _run();
    void esperarMesa();
    void pedirPlatos();
    void esperarEnElLiving();
    bool pedirOtroPlato();
    void pedirCuenta();
    void semaforoEsperar();

};


#endif //TP1_CLIENTE_H
