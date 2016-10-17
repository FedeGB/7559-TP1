//
// Created by fedenote on 10/12/16.
//

#ifndef TP1_CAJA_H
#define TP1_CAJA_H

#include "MemoriaCompartida.h"
#include "../Constantes.h"
#include "LockFile.h"

class Caja {

private:
    MemoriaCompartida<float> dinero;
    MemoriaCompartida<float> dineroSinCobrar;
public:
    Caja();
    ~Caja();
    void abrirCaja();
    float consultarDinero();
    float consultarDineroPerdido();
    void agregarDinero(float deposito);
    void agregarDineroSinCobrar(float deposito);
    void cerrarCaja();
};


#endif //TP1_CAJA_H
