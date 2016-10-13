//
// Created by mafv on 09/10/16.
//

#include "GeneradorClientes.h"

GeneradorClientes::GeneradorClientes(){

}

pid_t GeneradorClientes::cargarClientes() {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador clientes");

    }

    if (pid == 0) {

        fifoRecepcionLectura->abrir();
        fifoLivingLectura->abrir();

        for (int i = 0; i < CLIENTES; ++i) {

            Cliente cliente(i);
            this->configurarCliente(cliente);
            cliente.run();

        }

        for (int i = 0; i < CLIENTES; ++i) {

            wait(NULL);

        }

        fifoRecepcionLectura->cerrar();
        fifoLivingLectura->cerrar();

        delete fifoLivingLectura;
        delete fifoRecepcionLectura;
        delete sem_entrada;
        delete sem_recepcion;
        delete sem_living;

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

void GeneradorClientes::configurarCliente(Cliente &cliente) {

    cliente.setSem_recepcion(sem_recepcion);
    cliente.setSem_living(sem_living);
    cliente.setSem_entrada(sem_entrada);
    cliente.setFifoRecepcionLectura(fifoRecepcionLectura);
    cliente.setFifoLivingLectura(fifoLivingLectura);

}
