//
// Created by mafv on 15/10/16.
//

#include "Gerente.h"

void Gerente::setAdministradorLiving(AdministradorLiving *administradorLiving) {
    Gerente::administradorLiving = administradorLiving;
}

void Gerente::setCaja(Caja *caja) {
    Gerente::caja = caja;
}

void Gerente::_run() {

    Logger::getInstance().log("Soy el gerente y el total de la caja es: " + std::to_string(caja->consultarDinero()));
    Logger::getInstance().log("Soy el gerente y en el living esperaron: " + std::to_string(administradorLiving->clientesQueEsperaronEnElLiving()) + " clientes");

}
