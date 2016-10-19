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
    consultar = true;
    MemoriaCompartida<bool> gerenteConsulta;
    gerenteConsulta.crear(MEMORIA_COMPARTIDA_GERENTE_CONSULTA, 'G');
    while(this->consultar) {
        Logger::getInstance().log(
                "\n\n\n\n\n\nSoy el gerente y el total de la caja es: " + std::to_string(caja->consultarDinero()));
        Logger::getInstance().log("Soy el gerente y el total perdido por cortes de luz es: " +
                                  std::to_string(caja->consultarDineroPerdido()));
        Logger::getInstance().log("Soy el gerente y en el living esperaron: " +
                                  std::to_string(administradorLiving->clientesQueEsperaronEnElLiving()) + " clientes");
        sleep(20); // Cada 20 segundos
        this->consultar = gerenteConsulta.leer();
    }
}


void Gerente::atenderSenial() {
    Logger::getInstance().log("Gerente se corto la luz, me preocupo por mi restaurante");
}

void Gerente::setSigint_handler(SIGINT_Handler *sigint_handler) {

    this->sigint_handler = sigint_handler;

}
