//
// Created by mafv on 12/10/16.
//

#include "GeneradorMozos.h"

GeneradorMozos::GeneradorMozos(int cantidadDeMozos) {
    this->cantidadDeMozos = cantidadDeMozos;
}

pid_t GeneradorMozos::cargarMozos() {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador mozos");

    }

    if (pid == 0) {

        fifoMozosLectura->abrir();


        for (int i = 0; i < cantidadDeMozos; ++i) {

            Mozo mozo(i);
            this->configurarMozos(mozo);
            mozo.run();

        }

        for (int i = 0; i < cantidadDeMozos; ++i) {

            wait(NULL);

        }

        fifoMozosLectura->cerrar();

        delete fifoMozosLectura;
        for(auto const &ent1 : semaforosPedidoDeMesas) {

            delete ent1.second;

        }

        exit(0);

    } else {

        return pid;

    }

}


void GeneradorMozos::setSemaforosPedidoDeMesas(const std::map<int, Semaforo *> &semaforosPedidoDeMesas) {
    GeneradorMozos::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void GeneradorMozos::setFifoMozosLectura(FifoLectura *fifoMozosLectura) {
    GeneradorMozos::fifoMozosLectura = fifoMozosLectura;
}

void GeneradorMozos::configurarMozos(Mozo &mozo) {

    mozo.setFifoPedidoMozo(fifoMozosLectura);
    mozo.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);

}


