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
public:
    Caja();
    ~Caja();
    float consultarDinero();
    void agregarDinero(float deposito);
    void cerrarCaja();
};


#endif //TP1_CAJA_H