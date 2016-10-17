//
// Created by mariano on 17/10/16.
//

#ifndef TP1_GENERADORDECOCINERO_H
#define TP1_GENERADORDECOCINERO_H


#include "Menu.h"
#include "Estructuras/FifoLectura.h"
#include "Estructuras/FifoEscritura.h"
#include "Estructuras/SIGINT_Handler.h"
#include "Procesos/Cocinero.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorDeCocinero : public AtenderSignal {

private:
    FifoEscritura *fifoMozosCocineroEscritura;

    FifoLectura *fifoCocineroLectura;

    Menu *menu;

    bool existioCorteDeLuz;

    int cortesDeLuz;

    SIGINT_Handler *sigint_handler;

    pid_t pidCocinero;

public:

    GeneradorDeCocinero();

    pid_t cargarCocinero();

    void setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura);

    void setFifoCocineroLectura(FifoLectura *fifoCocineroLectura);

    void setMenu(Menu *menu);

    void setSigint_handler(SIGINT_Handler *sigint_handler);

    void atenderSenial();

private:

    void configurarCocinero(Cocinero &cocinero);

    void crearCocineroDespuesDelCorte();

};


#endif //TP1_GENERADORDECOCINERO_H
