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

private:
    int cantidadDeMesas;
    std::string nombre;
    FifoEscritura *fifoRecepcionEscritura;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
public:

    Recepcionista(std::string nombre, int cantidadDeMesas);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setFifoRecepcionEscritura(FifoEscritura *fifoRecepcionEscritura);

    ~Recepcionista();

private:
    void _run();
    void asignarMesa();
};


#endif //TP1_RECEPCIONISTA_H
