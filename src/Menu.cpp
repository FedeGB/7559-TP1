//
// Created by fedenote on 9/10/16.
//

#include "Menu.h"

Menu::Menu() {
}

bool Menu::fill(std::string) {
    return  true;
}

PlatoComida Menu::eleccionRandom() {
    if(this->platosDisponibles.empty()) {
        throw "No se cargo ningun plato al Menu.";
    }
    srand(time(NULL));
    int seleccion = rand() % this->platosDisponibles.size();
    if(seleccion >= this->platosDisponibles.size()) {
        throw "Error de seleccion, evitando seg fault";
    }
    return PlatoComida(this->platosDisponibles[seleccion]);
}