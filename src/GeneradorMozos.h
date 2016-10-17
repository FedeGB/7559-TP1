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
#include "Menu.h"
#include "Estructuras/Pipe.h"
#include "Logger.h"
#include "Estructuras/SIGINT_Handler.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorMozos : public AtenderSignal {
private:
    std::vector<pid_t> pidMozos;
    int cantidadDeMozos;
    std::map<int,Semaforo> semaforosPedidoDeMesas;
    std::map<int,Semaforo> semaforosSaldos;
    FifoLectura *fifoMozosLectura;
    FifoEscritura *fifoCocineroEscritura;
    FifoLectura *fifoMozosCocineroLectura;
    Menu *menu;
    bool existioCorteDeLuz;
    int cortesDeLuz;
    SIGINT_Handler *sigint_handler;

public:

    GeneradorMozos(int cantidadDeMozos);

    GeneradorMozos();

    void setCantidadDeMozos(int cantidadDeMozos);

    pid_t cargarMozos();

    void setFifoMozosLectura(FifoLectura *fifoMozosLectura);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas);

    void setFifoCocineroEscritura(FifoEscritura *f);

    void setFifoMozosCocineroLectura(FifoLectura *f);

    void setMenu(Menu *menu);

    void setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos);

    void atenderSenial();

    void setSigint_handler(SIGINT_Handler *sigint_handler);

private:

    void configurarMozos(Mozo &mozo);

    void crearMozos();

    void esperarMozos();

    void crearMozosDespuesDelCorte();

};


#endif //TP1_GENERADORMOZOS_H
