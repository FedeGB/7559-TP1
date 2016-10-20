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
#include "../AtenderSignal.h"
#include "../Estructuras/SIGINT_Handler.h"
#include "../Logger.h"

class Cocinero: public Proceso, public AtenderSignal {

private:

    FifoEscritura *fifoMozosCocineroEscritura;

    FifoLectura *fifoCocineroLectura;

    Menu *menu;

    int cortesDeLuz;

    SIGINT_Handler *sigint_handler;

public:

    Cocinero();

    Cocinero(int cortesDeLuz);

    void setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura);

    void setFifoCocineroLectura(FifoLectura * f);

    void setMenu(Menu *menu);

    void setSigint_handler(SIGINT_Handler *sigint_handler);

    void atenderSenial();

private:

    void _run();

    void enviarComidaAMozos(const ordenDeComida &orden);
};


#endif //TP1_COCINERO_H
