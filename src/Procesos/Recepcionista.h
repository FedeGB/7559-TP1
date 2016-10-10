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
#include "../Estructuras/FifoEscritura.h"
#include "../Constantes.h"
#include "../Mesas.h"
#include "../Estructuras/MemoriaCompartida2.h"
#include <unistd.h>

class Recepcionista : public Proceso {
public:
    Recepcionista(std::string nombre, Semaforo sem_entrada,
                  Semaforo sem_recepcion,FifoEscritura fifoRecepcionEscritura,int cantidadDeMesas);

    ~Recepcionista();
private:
    int cantidadDeMesas;
    std::string nombre;
    Semaforo sem_entrada;
    Semaforo sem_recepcion;
    FifoEscritura fifoRecepcionEscritura;
    MemoriaCompartida2<Mesas> *memoria;

    void _run();
    void asignarMesa();
};


#endif //TP1_RECEPCIONISTA_H
