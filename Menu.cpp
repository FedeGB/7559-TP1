//
// Created by fedenote on 9/10/16.
//

#include "Menu.h"

Menu::Menu(std::string path) {
/* TODO: A definir si se hace el open de vuelta, si se pasa el file
  o si se tiene ya algo bien parceado como constructor */
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