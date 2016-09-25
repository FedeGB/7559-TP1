//
// Created by horacio on 9/24/16.
//

#include <unistd.h>
#include "Recepcionista.h"
#include "Logger.h"
#include "Semaforo.h"
#include "IDSemaforos.h"
#include "Utils.h"

Recepcionista :: Recepcionista (std::string nombre) :nombre(nombre){
}

void Recepcionista::_run() {
    Logger::getInstance().log("Recepcionista " + nombre + " creado");

    Semaforo sem_entrada(ARCHIVO_SEMAFOROS_ENTRADA, SEM_ENTRADA, 0);
    sem_entrada.get();
    Semaforo sem_recepcion(ARCHIVO_SEMAFOROS_ENTRADA, SEM_RECEPCION, 0);
    sem_recepcion.get();

    while (sem_entrada.decrementar() > -1){ //mientras haya clientes en la entrada (si no hay niguno bloque aca)

        //recibo a cliente:
        sem_recepcion.incrementar();
        Logger::getInstance().log("Recepcionista " + nombre + " esta atendiendo a un cliente");

        sleep(5 + getRandomInt(1,5)); // tiempo que tardo en atenderlo
        Logger::getInstance().log("Recepcionista " + nombre + " termino de atender a un cliente");
    }
}