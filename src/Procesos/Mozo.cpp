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

void Mozo::setSemaforosPedidoDeMesas(const std::map<int, Semaforo *> &semaforosPedidoDeMesas) {
    Mozo::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void Mozo::setFifoCocineroEscritura(FifoEscritura* f){
    this->fifoCocineroEscritura = f;
}

Mozo::Mozo() {

}

void Mozo::_run() {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " creado");

    char* buffer;

    fifoPedidoMozo->obtenerCopia();
    fifoMozosCocineroLectura->obtenerCopia();
    fifoCocineroEscritura->obtenerCopia();

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
            Logger::getInstance().log("no deberia llegar aca");
            throw 2;
//            this->entregarPedidoAlCliente();

        }

    }

    Logger::getInstance().log("Mozo " + std::to_string(id) +" No Hay mas clientes me retiro");

    clientesPorComer.liberar();

    fifoPedidoMozo->cerrar();
    fifoMozosCocineroLectura->cerrar();
    fifoCocineroEscritura->cerrar();

    delete fifoPedidoMozo;
    delete fifoMozosCocineroLectura;
    delete fifoCocineroEscritura;

    for(auto const &ent1 : semaforosPedidoDeMesas) {

        delete ent1.second;

    }

}

void Mozo::solicitarPedidoAlCocinero() {

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibi un pedido de la meza: " + std::to_string(pedido.numeroDeMesa));

    sleep(3);

    int platoSolicitado = getRandomInt(1,14); // TODO: el numero de plato ( o struct) debe venir del cliente

    ordenDeComida orden;
    orden.numeroDeMesa = pedido.numeroDeMesa;
    orden.numeroPlato = platoSolicitado;

    fifoCocineroEscritura->escribir(&orden,sizeof(ordenDeComida));

    Logger::getInstance().log("Mozo " + std::to_string(id) + " pidio plato " +  std::to_string(orden.numeroPlato)
                              +" de la mesa " + std::to_string(orden.numeroDeMesa) + " al cocinero");

    //todo: lock aca ?
    indicacionAlMozo comidaParaEntregar;
    fifoMozosCocineroLectura->leer(&comidaParaEntregar,sizeof(indicacionAlMozo));

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibio plato del cocinero para la mesa: " + std::to_string(comidaParaEntregar.numeroDeMesa));

    this->entregarPedidoAlCliente(comidaParaEntregar.numeroDeMesa);

}

void Mozo::entregarPedidoAlCliente(int numeroDeMesa) {

    //Estas dos lineas irian en el metodo entregarPedidoAlCliente

    Logger::getInstance().log("Mozo " + std::to_string(id) + " entrego pedido a la meza: " + std::to_string(numeroDeMesa));

    semaforosPedidoDeMesas[numeroDeMesa]->v();

}
