//
// Created by mafv on 13/10/16.
//

#ifndef TP1_CLIENTESPORCOMER_H
#define TP1_CLIENTESPORCOMER_H


#include <vector>
#include "Estructuras/MemoriaCompartida.h"

class ClientesPorComer {

private:
    MemoriaCompartida<int> clientesQueFaltanComer;
    int cantidadDeClientes;
public:
    ClientesPorComer();
    ClientesPorComer(int);
    void inicializar();
    void descontarCliente();
    void liberar();
    bool quedanClientes();
    void setCantidadDeClientesDisponibles(int);
};


#endif //TP1_CLIENTESPORCOMER_H
