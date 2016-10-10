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
#include "AdministradorLiving.h"
#include "Logger.h"

class Mesas {

private:
    int numeroDeMesas;
    std::vector< MemoriaCompartida<bool> > memorias;

public:

    Mesas(int numeroDeMesas);
    Mesas();

    void armarMesas();

    void desarmarMesas();

    int obtenerMesaLibre();

    int obtenerMesaDesocupada();

    void desocuparMesa(int numeroDeMesa);

    ~Mesas();

private:

    bool verificarSiHayClientesEnElLiving();
    int buscarMesaLibre();

};


#endif //TP1_MESAS_H
