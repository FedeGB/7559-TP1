//
// Created by horacio on 9/24/16.
//

#ifndef TP1_RECEPCIONISTA_H
#define TP1_RECEPCIONISTA_H


#include <bits/stringfwd.h>
#include "Utils.h"
#include "Proceso.h"
#include <string>
#include "Logger.h"
#include "Semaforo.h"
#include "IDSemaforos.h"
#include <unistd.h>

class Recepcionista : public Proceso {
public:
    Recepcionista(std::string nombre);

private:
    std::string nombre;
    void _run();
};


#endif //TP1_RECEPCIONISTA_H
