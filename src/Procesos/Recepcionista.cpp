//
// Created by horacio on 9/24/16.
//

#include "Recepcionista.h"

Recepcionista::Recepcionista(std::string nombre, Semaforo sem_entrada,Semaforo sem_recepcion) : nombre(nombre), sem_entrada(sem_entrada),
                                                                               sem_recepcion(sem_recepcion) {
}

void Recepcionista::_run() {
    Logger::getInstance().log("Recepcionista " + nombre + " creado");

    while (sem_entrada.p() > -1) { //mientras haya clientes en la entrada (si no hay niguno bloque aca)

        //recibo a cliente:
        sem_recepcion.v();
        Logger::getInstance().log("Recepcionista " + nombre + " esta atendiendo a un cliente");

        sleep(5 + getRandomInt(1, 5)); // tiempo que tardo en atenderlo
        Logger::getInstance().log("Recepcionista " + nombre + " termino de atender a un cliente");
    }

}