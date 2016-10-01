//
// Created by horacio on 9/19/16.
//

#include "Cliente.h"


Cliente::Cliente(int id, int plata, Semaforo sem_entrada, Semaforo sem_recepcion) : id(id), plata(plata),
                                                                                    sem_entrada(sem_entrada),
                                                                                    sem_recepcion(sem_recepcion) {
}

void Cliente::_run() {
    Logger::getInstance().log("Creado cliente " + std::to_string(id) + ", con plata " + std::to_string(plata));

    sem_entrada.v(); // meto al cliente en la entrada, si no habia ninguno los recepcionistas estaban bloqueados aca esperando
    Logger::getInstance().log("cliente " + std::to_string(id) + " llego a la entrada");

    // espero a que me "recepcionen", si no hay ningun recepcionista bloquea aca
    sem_recepcion.p();
    Logger::getInstance().log("cliente " + std::to_string(id) + " fue atendido por un recepcionista");
}