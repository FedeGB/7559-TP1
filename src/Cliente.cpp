//
// Created by horacio on 9/19/16.
//

#include "Cliente.h"
#include "Logger.h"

Cliente::Cliente(int plata) {
    this->plata = plata;
}

void Cliente::_run() {
    std::cout << "Soy un proceso cliente, tengo plata " << plata << std::endl;
//    Logger::getInstance().log("Soy un proceso cliente, tengo plata " + plata);
}