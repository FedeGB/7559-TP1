//
// Created by mafv on 09/10/16.
//

#include "GeneradorClientes.h"

GeneradorClientes::GeneradorClientes(){

}

GeneradorClientes::GeneradorClientes(int cantClientes){
    cantidadDeClientes = cantClientes;
}

pid_t GeneradorClientes::cargarClientes() {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador clientes");

    }

    if (pid == 0) {
        fifoRecepcionLectura->abrir();
        fifoLivingLectura->abrir();
        fifoMozosEscritura->abrir();

        for (int i = 0; i < cantidadDeClientes; ++i) {

            Cliente cliente(i);
            this->configurarCliente(cliente);
            cliente.run();

        }

        for (int i = 0; i < cantidadDeClientes; ++i) {

            wait(NULL);

        }

        fifoRecepcionLectura->cerrar();
        fifoLivingLectura->cerrar();
        fifoMozosEscritura->cerrar();

        //delete fifoLivingLectura;
        //delete fifoRecepcionLectura;
        //delete fifoMozosEscritura;
        //delete sem_entrada;
        //delete sem_recepcion;
        //delete sem_living;

        /*for(auto const &ent1 : semaforosPedidoDeMesas) {

            delete ent1.second;

        }*/

        exit(0);

    } else {

        return pid;

    }

}

void GeneradorClientes::setFifoRecepcionLectura(FifoLectura *fifoRecepcionLectura) {
    GeneradorClientes::fifoRecepcionLectura = fifoRecepcionLectura;
}

void GeneradorClientes::setFifoLivingLectura(FifoLectura *fifoLivingLectura) {
    GeneradorClientes::fifoLivingLectura = fifoLivingLectura;
}

void GeneradorClientes::setSem_entrada(Semaforo *sem_entrada) {
    GeneradorClientes::sem_entrada = sem_entrada;
}

void GeneradorClientes::setSem_recepcion(Semaforo *sem_recepcion) {
    GeneradorClientes::sem_recepcion = sem_recepcion;
}

void GeneradorClientes::setSem_living(Semaforo *sem_living) {
    GeneradorClientes::sem_living = sem_living;
}


void GeneradorClientes::setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura) {
    GeneradorClientes::fifoMozosEscritura = fifoMozosEscritura;
}

void GeneradorClientes::setSemaforosPedidoDeMesas(const std::map<int, Semaforo > &semaforosPedidoDeMesas) {
    GeneradorClientes::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}


void GeneradorClientes::configurarCliente(Cliente &cliente) {

    cliente.setSem_recepcion(sem_recepcion);
    cliente.setSem_living(sem_living);
    cliente.setSem_entrada(sem_entrada);
    cliente.setFifoRecepcionLectura(fifoRecepcionLectura);
    cliente.setFifoLivingLectura(fifoLivingLectura);
    cliente.setFifoMozosEscritura(fifoMozosEscritura);
    cliente.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    cliente.setMenu(menu);
    cliente.setSemaforosSaldos(semaforosSaldos);

}

void GeneradorClientes::setMenu(Menu *menu) {
    GeneradorClientes::menu = menu;
}

void GeneradorClientes::setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos) {
    GeneradorClientes::semaforosSaldos = semaforosSaldos;
}

void GeneradorClientes::setCantidadDeClientes(int cantClientes) {
    cantidadDeClientes = cantClientes;
}
