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

    Semaforo sem_entrada(ARCHIVO_SEMAFOROS_ENTRADA, SEM_ENTRADA, 0);
    sem_entrada.get();
    Semaforo sem_recepcion(ARCHIVO_SEMAFOROS_ENTRADA, SEM_RECEPCION, 0);
    sem_recepcion.get();

    sem_entrada.incrementar(); // meto al cliente en la entrada, si no habia ninguno los recepcionistas estaban bloqueados aca esperando
    Logger::getInstance().log("cliente " + std::to_string(id) + " llego a la entrada");

    // espero a que me "recepcionen", si no hay ningun recepcionista bloquea aca
    sem_recepcion.decrementar();
    Logger::getInstance().log("cliente " + std::to_string(id) + " fue atendido por un recepcionista");
}