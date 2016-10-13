//
// Created by mafv on 12/10/16.
//

#ifndef TP1_GENERADORMOZOS_H
#define TP1_GENERADORMOZOS_H


#include <map>
#include "Estructuras/Semaforo.h"
#include "Estructuras/FifoLectura.h"
#include "Procesos/Mozo.h"
#include "Estructuras/FifoEscritura.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorMozos {
private:
    int cantidadDeMozos;
    std::map<int,Semaforo*> semaforosPedidoDeMesas;
    FifoLectura *fifoMozosLectura;
    FifoEscritura *fifoCocineroEscritura;

public:

    GeneradorMozos(int cantidadDeMozos);

    pid_t cargarMozos();

    void setFifoMozosLectura(FifoLectura *fifoMozosLectura);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo *> &semaforosPedidoDeMesas);

    void setFifoCocineroEscritura(FifoEscritura *f);

private:

    void configurarMozos(Mozo &mozo);

};


#endif //TP1_GENERADORMOZOS_H
