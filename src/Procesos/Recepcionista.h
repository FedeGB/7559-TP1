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
#include "../AtenderSignal.h"
#include "../Estructuras/SIGINT_Handler.h"
#include <unistd.h>

class Recepcionista : public Proceso,public AtenderSignal {

private:
    int cantidadDeMesas;
    std::string nombre;
    FifoEscritura *fifoRecepcionEscritura;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    SIGINT_Handler *sigint_handler;
    Semaforo *sem_espera_luz;

public:

    Recepcionista(std::string nombre, int cantidadDeMesas);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setFifoRecepcionEscritura(FifoEscritura *fifoRecepcionEscritura);

    void setSigint_handler(SIGINT_Handler *sigint_handler);

    void setSem_espera_luz(Semaforo *sem_espera_luz);

    void atenderSenial();

    ~Recepcionista();

private:
    void _run();
    void asignarMesa();
};


#endif //TP1_RECEPCIONISTA_H
