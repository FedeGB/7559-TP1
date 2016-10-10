//
// Created by mafv on 09/10/16.
//

#include "GeneradorClientes.h"

GeneradorClientes::GeneradorClientes(){

}

pid_t GeneradorClientes::cargarClientes(Semaforo sem_entrada, Semaforo sem_recepcion,FifoLectura fifoRecepcionLectura) {

    pid_t pid = fork();

    if (pid == -1) {

        throw std::runtime_error("Error al crear proceso generador clientes");

    }

    if (pid == 0) {

        fifoRecepcionLectura.abrir();

        for (int i = 0; i < CLIENTES; ++i) {

            Cliente cliente(i, sem_entrada, sem_recepcion,fifoRecepcionLectura);
            cliente.run();

        }

        for (int i = 0; i < CLIENTES; ++i) {

            wait(NULL);

        }

        fifoRecepcionLectura.cerrar();

        exit(0);

    } else {

        return pid;

    }

}
