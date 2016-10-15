//
// Created by horacio on 10/13/16.
//

#ifndef TP1_COCINERO_H
#define TP1_COCINERO_H


#include "Proceso.h"
#include "../Estructuras/FifoEscritura.h"
#include "../Estructuras/FifoLectura.h"
#include "../Menu.h"
#include "../Constantes.h"

class Cocinero: public Proceso {

private:

    FifoEscritura *fifoMozosCocineroEscritura;

    FifoLectura *fifoCocineroLectura;

    Menu *menu;

public:

    Cocinero();

    void setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura);

    void setFifoCocineroLectura(FifoLectura * f);

    void setMenu(Menu *menu);

private:

    void _run();

    void enviarComidaAMozos(const ordenDeComida &orden);
};


#endif //TP1_COCINERO_H
