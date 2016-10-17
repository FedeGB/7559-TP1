//
// Created by mafv on 12/10/16.
//

#include "Mozo.h"
#include "../Logger.h"
#include "../ClientesPorComer.h"
#include "../Estructuras/FifoEscritura.h"
#include "../Utils.h"
#include "SaldoDeMesa.h"
#include "../Estructuras/Caja.h"


Mozo::Mozo(int id) {
    this->id = id;
    this->cortesDeLuz = 0;
    Logger::getInstance().log("Mozo " + std::to_string(id) + " empiezo a trabajar");
}

Mozo::Mozo(int id, int cortesDeLuz) {
    this->id = id;
    this->cortesDeLuz = cortesDeLuz;
    Logger::getInstance().log("Mozo " + std::to_string(id) + " retorno despues del corte de luz");
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

    //Logger::getInstance().log("Mozo " + std::to_string(id) + " creado");

    this->sigint_handler->setAtenderSignal(this);

    fifoPedidoMozo->obtenerCopia();
    fifoMozosCocineroLectura->obtenerCopia();
    fifoCocineroEscritura->obtenerCopia();

    LockFile lock(LOCK_MOZOS);

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

        if(pedido.cortesDeLuz != this->cortesDeLuz){
            continue;
        }

        if(pedido.pedidoDeCuenta){

            this->buscarSaldoAPagar(pedido);

        } else {

            this->solicitarPedidoAlCocinero(pedido);

        }

    }

    Logger::getInstance().log("Mozo " + std::to_string(id) +" No Hay mas clientes me retiro");

    fifoPedidoMozo->cerrar();
    fifoMozosCocineroLectura->cerrar();
    fifoCocineroEscritura->cerrar();

}

void Mozo::solicitarPedidoAlCocinero(ordenDeComida orden) {

    SaldoDeMesa saldo;

    saldo.agregarSaldo(orden.numeroDeMesa,menu->getPlato(orden.numeroPlato).getPrecio());

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibio un pedido de la mesa: " + std::to_string(orden.numeroDeMesa));

    sleep(3);
    fifoCocineroEscritura->escribir(&orden,sizeof(orden));

    Logger::getInstance().log("Mozo " + std::to_string(id) + " pidio plato " +  menu->getPlato(orden.numeroPlato).getNombre()
                              +" de la mesa " + std::to_string(orden.numeroDeMesa) + " al cocinero");

    LockFile lock(LOCK_MOZOS_LECTURA_COMIDA_DE_COCINERO);
    lock.tomarLock();
    ordenDeComida comidaParaEntregar;
    fifoMozosCocineroLectura->leer(&comidaParaEntregar,sizeof(comidaParaEntregar));
    lock.liberarLock();

    if(comidaParaEntregar.cortesDeLuz != this->cortesDeLuz ) {
        return;
    }

    Logger::getInstance().log("Mozo " + std::to_string(id) + " recibio plato "+ menu->getPlato(comidaParaEntregar.numeroPlato).getNombre() +" del cocinero para la mesa: " + std::to_string(comidaParaEntregar.numeroDeMesa));

    this->entregarPedidoAlCliente(comidaParaEntregar);

}

void Mozo::entregarPedidoAlCliente(ordenDeComida comidaParaEntregar) {

    //Estas dos lineas irian en el metodo entregarPedidoAlCliente

    Logger::getInstance().log("Mozo " + std::to_string(id) + " entrego pedido a la meza: " + std::to_string(comidaParaEntregar.numeroDeMesa));

    //sleep(3);

    semaforosPedidoDeMesas[comidaParaEntregar.numeroDeMesa].v();

}

void Mozo::setMenu(Menu *menu) {
    Mozo::menu = menu;
}

void Mozo::buscarSaldoAPagar(ordenDeComida pedido) {

    Logger::getInstance().log("Soy el Mozo " + std::to_string(id) + " y voy a consultar lo que debe la mesa " + std::to_string(pedido.numeroDeMesa));

    SaldoDeMesa saldo;
    float totalACobrar = saldo.obtenerSaldo(pedido.numeroDeMesa);

    Logger::getInstance().log("Soy el Mozo " + std::to_string(id) + " y el cliente de la mesa " + std::to_string(pedido.numeroDeMesa)+" debe pagar "+std::to_string(totalACobrar));

    semaforosPedidoDeMesas[pedido.numeroDeMesa].v();

    semaforosSaldos[pedido.numeroDeMesa].p();

    Logger::getInstance().log("Soy el Mozo " + std::to_string(id) + " y recibi el pago de la mesa " + std::to_string(pedido.numeroDeMesa));

    saldo.reiniciar(pedido.numeroDeMesa);

    Caja caja;

    caja.agregarDinero(totalACobrar);

}

void Mozo::setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos) {
    Mozo::semaforosSaldos = semaforosSaldos;
}


void Mozo::atenderSenial() {

    Logger::getInstance().log("Soy el Mozo " + std::to_string(id) + "espero a que vuelva la luz");
    fifoPedidoMozo->cerrar();
    fifoMozosCocineroLectura->cerrar();
    fifoCocineroEscritura->cerrar();
    LockFile lock(LOCK_MOZOS);
    lock.liberarLock();
    LockFile lock2(LOCK_MOZOS_LECTURA_COMIDA_DE_COCINERO);
    lock2.liberarLock();

    exit(0);

}


void Mozo::setSigint_handler(SIGINT_Handler *sigint_handler) {

    this->sigint_handler = sigint_handler;

}
