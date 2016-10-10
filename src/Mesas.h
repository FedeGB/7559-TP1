//
// Created by mafv on 10/10/16.
//

#ifndef TP1_MESAS_H
#define TP1_MESAS_H

#include <map>
#include <vector>
#include "Constantes.h"
#include "Estructuras/LockFile.h"
#include "Estructuras/MemoriaCompartida.h"

class Mesas {

public:

    Mesas(int numeroDeMesas);

    void armarMesas();

    void desarmarMesas();

    int obtenerMesaLibre();

    ~Mesas();

private:
    int numeroDeMesas;
    //LockFile *lock;
    std::vector< MemoriaCompartida<bool> > memorias;

};


#endif //TP1_MESAS_H
