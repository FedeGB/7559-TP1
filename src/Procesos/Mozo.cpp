//
// Created by mafv on 12/10/16.
//

#include "Mozo.h"
#include "../Logger.h"
#include "../ClientesPorComer.h"


Mozo::Mozo(int id) {
    this->id = id;
}

void Mozo::setFifoPedidoMozo(FifoLectura *fifoPedidoMozo) {
    Mozo::fifoPedidoMozo = fifoPedidoMozo;
}

void Mozo::setSemaforosPedidoDeMesas(const std::map<int, Semaforo *> &semaforosPedidoDeMesas) {
    Mozo::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

Mozo::Mozo() {

}

void Mozo::_run() {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " creado");

    char* buffer;

    fifoPedidoMozo->obtenerCopia();

    LockFile lock(LOCK_MOZOS);

    ClientesPorComer clientesPorComer;

    while(clientesPorComer.quedanClientes()) {

        lock.tomarLock();

        buffer = new char[sizeof(pedido)];

        ssize_t leido = fifoPedidoMozo->leer(buffer,sizeof(pedido));

        //Se cerro el fifo de los clientes
        if(leido == 0){

            lock.liberarLock();
            delete buffer;
            break;

        }

        lock.liberarLock();

        memcpy(&pedido,buffer,sizeof(pedido));

        delete buffer;

        if(pedido.pedido){

            this->solicitarPedidoAlCocinero();

        } else {

            this->entregarPedidoAlCliente();

        }

    }

    Logger::getInstance().log("Mozo " + std::to_string(id) +" No Hay mas clientes me retiro");

    clientesPorComer.liberar();

    fifoPedidoMozo->cerrar();

    delete fifoPedidoMozo;

    for(auto const &ent1 : semaforosPedidoDeMesas) {

        delete ent1.second;

    }

}

void Mozo::solicitarPedidoAlCocinero() {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibi un pedido de la meza: " + std::to_string(pedido.numeroDeMesa));

    sleep(3);

    Logger::getInstance().log("Mozo " + std::to_string(id) + " no hay cocinero, por lo que entrego plato vacio");


    //Estas dos lineas irian en el metodo entregarPedidoAlCliente
    Logger::getInstance().log("Mozo " + std::to_string(id) + " entrego pedido a la meza: " + std::to_string(pedido.numeroDeMesa));

    semaforosPedidoDeMesas[pedido.numeroDeMesa]->v();

}

void Mozo::entregarPedidoAlCliente() {

}
