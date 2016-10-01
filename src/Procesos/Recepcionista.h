//
// Created by horacio on 9/24/16.
//

#ifndef TP1_RECEPCIONISTA_H
#define TP1_RECEPCIONISTA_H


#include <bits/stringfwd.h>
#include "../Utils.h"
#include "Proceso.h"
#include <string>
#include "../Logger.h"
#include "../Estructuras/Semaforo.h"
#include "../Estructuras/IDSemaforos.h"
#include <unistd.h>

class Recepcionista : public Proceso {
public:
    Recepcionista(std::string nombre, Semaforo sem_entrada,
                  Semaforo sem_recepcion);

private:
    std::string nombre;
    Semaforo sem_entrada;
    Semaforo sem_recepcion;

    void _run();
};


#endif //TP1_RECEPCIONISTA_H
