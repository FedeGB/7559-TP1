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
    fifoMozosCocineroEscritura->abrir();
    fifoMozosCocineroEscritura->obtenerCopia();
    fifoCocineroLectura->abrir();
    fifoCocineroLectura->obtenerCopia();

    while (1) {
        ordenDeComida orden;
        ssize_t leido = fifoCocineroLectura->leer(&orden, sizeof(ordenDeComida));

        //Se cerro el fifo del cocinero
        if (leido == 0) {
            break;
        }
        Logger::getInstance().log(
                "Cocinero recibio pedido de plato " + std::to_string(orden.numeroPlato) + " de la mesa " +
                std::to_string(orden.numeroDeMesa) + " ,procede a cocinarlo");

        // Tiempo de cocinar
        sleep(5);

        enviarComidaAMozos(orden.numeroPlato, orden.numeroDeMesa);
    }

    Logger::getInstance().log("COCINERO se las toma");

    fifoMozosCocineroEscritura->cerrar();
    fifoCocineroLectura->cerrar();
    delete fifoCocineroLectura;
    delete fifoMozosCocineroEscritura;
}

void Cocinero::enviarComidaAMozos(int numeroPlato, int numeroMesa) {

    //TODO: usar numeroPlato

    struct indicacionAlMozo entregaComida;

    entregaComida.numeroDeMesa = numeroMesa;
    entregaComida.pedido = false;


    Logger::getInstance().log(
            "Cocinero acaba de entregar a algun mozo comida para la mesa " + std::to_string(numeroMesa));

    fifoMozosCocineroEscritura->escribir(&entregaComida, sizeof(entregaComida));
}

void Cocinero::setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura) {
    this->fifoMozosCocineroEscritura = fifoMozosCocineroEscritura;
}

void Cocinero::setFifoCocineroLectura(FifoLectura *f) {
    this->fifoCocineroLectura = f;
}