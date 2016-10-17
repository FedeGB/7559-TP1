//
// Created by mafv on 12/10/16.
//

#include "GeneradorMozos.h"
#include "Estructuras/FifoEscritura.h"

GeneradorMozos::GeneradorMozos(int cantidadDeMozos) {
    this->cantidadDeMozos = cantidadDeMozos;
}


GeneradorMozos::GeneradorMozos() {
}

void GeneradorMozos::setCantidadDeMozos(int cantidadDeMozos) {
    this->cantidadDeMozos = cantidadDeMozos;
}

pid_t GeneradorMozos::cargarMozos() {

    SignalHandler :: getInstance()->registrarHandler ( SIGINT,this );
    this->existioCorteDeLuz = false;

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador mozos");

    }

    if (pid == 0) {

        fifoMozosLectura->abrir();
        fifoMozosCocineroLectura->abrir();
        fifoCocineroEscritura->abrir();

        this->crearMozos();

        this->esperarMozos();

        while( this->existioCorteDeLuz ) {

            this->existioCorteDeLuz = false;

            this->crearMozosDespuesDelCorte();

            this->esperarMozos();

        }

        fifoMozosLectura->cerrar();
        fifoMozosCocineroLectura->cerrar();
        fifoCocineroEscritura->cerrar();

        exit(0);

    } else {

        return pid;

    }

}


void GeneradorMozos::setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas) {
    GeneradorMozos::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void GeneradorMozos::setFifoMozosLectura(FifoLectura *fifoMozosLectura) {
    GeneradorMozos::fifoMozosLectura = fifoMozosLectura;
}

void GeneradorMozos::configurarMozos(Mozo &mozo) {

    mozo.setFifoPedidoMozo(fifoMozosLectura);
    mozo.setFifoMozosCocineroLectura(fifoMozosCocineroLectura);
    mozo.setFifoCocineroEscritura(fifoCocineroEscritura);
    mozo.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    mozo.setMenu(menu);
    mozo.setSemaforosSaldos(semaforosSaldos);

}

void GeneradorMozos::setFifoCocineroEscritura(FifoEscritura * f){
    this->fifoCocineroEscritura = f;
}

void GeneradorMozos::setFifoMozosCocineroLectura(FifoLectura *f) {
    this->fifoMozosCocineroLectura = f;
}

void GeneradorMozos::setMenu(Menu *menu) {
    GeneradorMozos::menu = menu;
}

void GeneradorMozos::setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos) {
    GeneradorMozos::semaforosSaldos = semaforosSaldos;
}


void GeneradorMozos::crearMozos() {

    for (int i = 0; i < cantidadDeMozos; ++i) {

        Mozo mozo(i);
        this->configurarMozos(mozo);
        pid_t pidMozo = mozo.run();

        pidMozos.push_back(pidMozo);

    }

}

void GeneradorMozos::esperarMozos() {

    for (int i = 0; i < cantidadDeMozos; ++i) {

        wait(NULL);

    }

}

void GeneradorMozos::crearMozosDespuesDelCorte() {

    for (int i = 0; i < cantidadDeMozos ; ++i) {

        Mozo mozo(i,cortesDeLuz);
        this->configurarMozos(mozo);
        pid_t pidMozo = mozo.run();

        pidMozos.push_back(pidMozo);

    }

}

void GeneradorMozos::atenderSenial() {

    this->existioCorteDeLuz = true;
    this->cortesDeLuz++;
    Logger::getInstance().log("CORTE DE LUZ"+std::to_string(this->cortesDeLuz));

    for(auto pid_mozo : pidMozos ) {

        kill(pid_mozo,CORTE_DE_LUZ);

    }

}


