//
// Created by mafv on 10/10/16.
//

#ifndef TP1_ADMINISTRADORLIVING_H
#define TP1_ADMINISTRADORLIVING_H


#include "Estructuras/MemoriaCompartida.h"
#include "Constantes.h"
#include "Estructuras/LockFile.h"

class AdministradorLiving {
private:
    MemoriaCompartida<int> clientesEnElLiving;
    MemoriaCompartida<int> cantidadDeClientesEnElLiving;
public:
    void armarLiving();
    void desarmarLiving();
    void agregarClienteAlLiving();
    void sacarClienteDelLiving();
    bool hayClientesEnElLiving();
    int clientesQueEsperaronEnElLiving();
    void limpiarLiving();
};


#endif //TP1_ADMINISTRADORLIVING_H
