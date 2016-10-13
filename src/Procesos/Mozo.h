//
// Created by mafv on 12/10/16.
//

#ifndef TP1_MOZO_H
#define TP1_MOZO_H


#include <map>
#include "Proceso.h"
#include "../Estructuras/FifoLectura.h"
#include "../Estructuras/Semaforo.h"
#include "../Estructuras/LockFile.h"
#include "../Constantes.h"

class Mozo : public Proceso {

private:

    int id;
    FifoLectura *fifoPedidoMozo;
    std::map<int,Semaforo*> semaforosPedidoDeMesas;
    struct indicacionAlMozo pedido;

public:

    Mozo(int id);
    Mozo();

    void setFifoPedidoMozo(FifoLectura *fifoPedidoMozo);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo *> &semaforosPedidoDeMesas);

private:

    void _run();

    void solicitarPedidoAlCocinero();

    void entregarPedidoAlCliente();

};


#endif //TP1_MOZO_H