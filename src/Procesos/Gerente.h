//
// Created by mafv on 15/10/16.
//

#ifndef TP1_GERENTE_H
#define TP1_GERENTE_H


#include "Proceso.h"
#include "../AdministradorLiving.h"
#include "../Estructuras/Caja.h"
#include "../Logger.h"
#include "../AtenderSignal.h"
#include "../Estructuras/SIGINT_Handler.h"
#include "../Estructuras/Semaforo.h"

class Gerente : public Proceso, public AtenderSignal {

private:

    AdministradorLiving *administradorLiving;
    Caja *caja;
    bool consultar;
    SIGINT_Handler *sigint_handler;

public:

    void setAdministradorLiving(AdministradorLiving *administradorLiving);

    void setCaja(Caja *caja);

    void setSigint_handler(SIGINT_Handler *sigint_handler);

private:

    void _run();

    void atenderSenial();
};


#endif //TP1_GERENTE_H
