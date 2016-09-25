//
// Created by horacio on 9/19/16.
//

#include <unistd.h>
#include "Cliente.h"
#include "Logger.h"
#include "Semaforo.h"
#include "IDSemaforos.h"

Cliente::Cliente(int id,int plata):id(id), plata(plata) {
}

void Cliente::_run() {
    Logger::getInstance().log("Creado cliente " + std::to_string(id)+ ", con plata " + std::to_string(plata));

    Semaforo sem_entrada("/tmp/asdasdasd", SEM_ENTRADA, 0);
    sem_entrada.get();
    Semaforo sem_recepcion("/tmp/as123d", SEM_RECEPCION, 0);
    sem_recepcion.get();

//    sem_entrada.crear();

    sem_entrada.v();
    Logger::getInstance().log("cliente " + std::to_string(id) + " llego a la entrada");

    // espero a que me "recepcionen"
    sem_recepcion.p();
    Logger::getInstance().log("cliente " + std::to_string(id) + " fue recepcionado");
}