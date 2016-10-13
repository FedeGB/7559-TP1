//
// Created by horacio on 10/13/16.
//

#ifndef TP1_COCINERO_H
#define TP1_COCINERO_H


#include "Proceso.h"
#include "../Estructuras/FifoEscritura.h"
#include "../Estructuras/FifoLectura.h"

class Cocinero: public Proceso {

public:
    Cocinero();
    void setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura);
    void setFifoCocineroLectura(FifoLectura * f);

private:
    FifoEscritura *fifoMozosEscritura;
    FifoLectura *fifoCocineroLectura;

    void _run();

    void enviarComidaAMozos(int numeroPlato,int numeroMesa);
};


#endif //TP1_COCINERO_H
