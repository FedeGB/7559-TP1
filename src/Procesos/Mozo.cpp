//
// Created by mafv on 12/10/16.
//

#include "Mozo.h"
#include "../Logger.h"
#include "../ClientesPorComer.h"
#include "../Estructuras/FifoEscritura.h"
#include "../Utils.h"


Mozo::Mozo(int id) {
    this->id = id;
}

void Mozo::setFifoPedidoMozo(FifoLectura *fifoPedidoMozo) {
    Mozo::fifoPedidoMozo = fifoPedidoMozo;
}

void Mozo::setFifoMozosCocineroLectura(FifoLectura * f){
    Mozo::fifoMozosCocineroLectura = f;
}

void Mozo::setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas) {
    Mozo::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void Mozo::setFifoCocineroEscritura(FifoEscritura* f){
    this->fifoCocineroEscritura = f;
}

Mozo::Mozo() {

}

void Mozo::_run() {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " creado");

    fifoPedidoMozo->obtenerCopia();
    fifoMozosCocineroLectura->obtenerCopia();
    fifoCocineroEscritura->obtenerCopia();

    LockFile lock(LOCK_MOZOS);

    //ClientesPorComer clientesPorComer;

    while(true) {

        lock.tomarLock();

        ordenDeComida pedido;

        ssize_t leido = fifoPedidoMozo->leer(&pedido,sizeof(pedido));

        //Se cerro el fifo de los clientes
        if(leido == 0){
            lock.liberarLock();
            break;
        }

        lock.liberarLock();


        this->solicitarPedidoAlCocinero(pedido);

    }

    Logger::getInstance().log("Mozo " + std::to_string(id) +" No Hay mas clientes me retiro");

    //clientesPorComer.liberar();

    fifoPedidoMozo->cerrar();
    fifoMozosCocineroLectura->cerrar();
    fifoCocineroEscritura->cerrar();

    //delete fifoPedidoMozo;
    //delete fifoMozosCocineroLectura;
    //delete fifoCocineroEscritura;

    /*for(auto const &ent1 : semaforosPedidoDeMesas) {

        delete ent1.second;

    }*/

}

void Mozo::solicitarPedidoAlCocinero(ordenDeComida orden) {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibio un pedido de la mesa: " + std::to_string(orden.numeroDeMesa));

    sleep(3);
    fifoCocineroEscritura->escribir(&orden,sizeof(orden));

    Logger::getInstance().log("Mozo " + std::to_string(id) + " pidio plato " +  std::to_string(orden.numeroPlato)
                              +" de la mesa " + std::to_string(orden.numeroDeMesa) + " al cocinero");

    //todo: lock aca ?
    ordenDeComida comidaParaEntregar;
    fifoMozosCocineroLectura->leer(&comidaParaEntregar,sizeof(comidaParaEntregar));

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibio plato del cocinero para la mesa: " + std::to_string(comidaParaEntregar.numeroDeMesa));

    this->entregarPedidoAlCliente(comidaParaEntregar);

}

void Mozo::entregarPedidoAlCliente(ordenDeComida comidaParaEntregar) {

    //Estas dos lineas irian en el metodo entregarPedidoAlCliente

    Logger::getInstance().log("Mozo " + std::to_string(id) + " entrego pedido a la meza: " + std::to_string(comidaParaEntregar.numeroDeMesa));

    //sleep(3);

    semaforosPedidoDeMesas[comidaParaEntregar.numeroDeMesa].v();

}
