//
// Created by horacio on 10/13/16.
//

#include "Cocinero.h"
#include "../Logger.h"
#include "../Constantes.h"
#include "../ClientesPorComer.h"

Cocinero::Cocinero() {
}

void Cocinero::_run() {

    fifoCocineroLectura->abrir();
    fifoCocineroLectura->obtenerCopia();
    fifoMozosEscritura->abrir();
    fifoMozosEscritura->obtenerCopia();


    ClientesPorComer clientesPorComer;

    while (clientesPorComer.quedanClientes()) {
        ordenDeComida orden;
        fifoCocineroLectura->leer(&orden, sizeof(ordenDeComida));
        Logger::getInstance().log("Cocinero recibio pedido de plato " + std::to_string(orden.numeroPlato) + " de la mesa " + std::to_string(orden.numeroDeMesa) + " ,procede a cocinarlo");

        // Tiempo de cocinar
        sleep(5);

        enviarComidaAMozos(orden.numeroPlato,orden.numeroDeMesa);
    }

    fifoMozosEscritura->cerrar();
    fifoCocineroLectura->cerrar();
    delete fifoCocineroLectura;
    delete fifoMozosEscritura;
}

void Cocinero::enviarComidaAMozos(int numeroPlato, int numeroMesa) {

    //TODO: usar numeroPlato

    struct indicacionAlMozo entregaComida;

    entregaComida.numeroDeMesa = numeroMesa;
    entregaComida.pedido = false;


    Logger::getInstance().log("Soy el cocinero y acabo de entregar a algun mozo comida para la mesa " + std::to_string(numeroMesa));

    fifoMozosEscritura->escribir(&entregaComida, sizeof(entregaComida));
}

void Cocinero::setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura) {
    this->fifoMozosEscritura = fifoMozosEscritura;
}

void Cocinero::setFifoCocineroLectura(FifoLectura *f) {
    this->fifoCocineroLectura = f;
}