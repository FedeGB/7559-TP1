//
// Created by mafv on 12/10/16.
//

#ifndef TP1_MOZO_H
#define TP1_MOZO_H


#include <map>
#include "Proceso.h"
#include "../Estructuras/FifoLectura.h"
#include "../Estructuras/Semaforo.h"
#include "../Estructuras/LockFile.h"
#include "../Constantes.h"
#include "../Estructuras/FifoEscritura.h"
#include "../Menu.h"
#include "../AtenderSignal.h"
#include "../Estructuras/SIGINT_Handler.h"
#include "SaldoDeMesa.h"
#include "../Estructuras/Caja.h"
#include "../Logger.h"

class Mozo : public Proceso , public AtenderSignal {

private:

    int id;
    FifoLectura *fifoPedidoMozo;
    FifoLectura *fifoMozosCocineroLectura;
    FifoEscritura *fifoCocineroEscritura;
    std::map<int,Semaforo> semaforosPedidoDeMesas;
    std::map<int, Semaforo> semaforosSaldos;
    Menu *menu;
    int cortesDeLuz;
    SIGINT_Handler *sigint_handler;

public:

    Mozo(int id);

    Mozo(int id, int cortesDeLuz);

    Mozo();

    void setFifoPedidoMozo(FifoLectura *fifoPedidoMozo);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas);

    void setFifoCocineroEscritura(FifoEscritura *f);

    void setFifoMozosCocineroLectura(FifoLectura *f);

    void setMenu(Menu *menu);

    void setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos);

    void atenderSenial();

    void setSigint_handler(SIGINT_Handler *sigint_handler);

private:

    void _run();

    void solicitarPedidoAlCocinero(ordenDeComida orden);

    void entregarPedidoAlCliente(ordenDeComida comidaParaEntregar);

    void buscarSaldoAPagar(ordenDeComida pedido);

};


#endif //TP1_MOZO_H
