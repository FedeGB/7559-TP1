//
// Created by mafv on 15/10/16.
//

#ifndef TP1_GERENTE_H
#define TP1_GERENTE_H


#include "Proceso.h"
#include "../AdministradorLiving.h"
#include "../Estructuras/Caja.h"
#include "../Logger.h"

class Gerente : public Proceso {

private:

    AdministradorLiving *administradorLiving;
    Caja *caja;

public:
    void setAdministradorLiving(AdministradorLiving *administradorLiving);

    void setCaja(Caja *caja);

private:

    void _run();

};


#endif //TP1_GERENTE_H
