//
// Created by fedenote on 9/10/16.
//

#include <iostream>
#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {
    std::vector<PlatoComida*>::iterator it = this->platosDisponibles.begin();
    while(it != this->platosDisponibles.end()) {
        if((*it) != NULL) {
            delete (*it);
        }
        it++;
    }
}

bool Menu::fill(std::string str) {
    size_t posOuter = 0;
    size_t posInner = 0;
    size_t prevOuter = 0;
    size_t prevInner = 0;
    int valueNumber;
    std::string delimiterMenu = ",";
    std::string delimiterPlato = "|";
    std::string tokenOuter;
    std::string tokenInner;
    PlatoComida* nuevoPlato;
    while ((posOuter = str.find(delimiterMenu)) != std::string::npos) {
        tokenOuter = str.substr(prevOuter, posOuter);
        valueNumber = 0;
        std::string nombrePlato = "";
        float precioPlato;
        prevInner = 0;
        std:: cout << tokenOuter << std::endl;
        while ((posInner = tokenOuter.find(delimiterPlato)) != std::string::npos) {
            tokenInner = tokenOuter.substr(prevInner, posInner);
            std::cout << tokenInner << std::endl;
            if(valueNumber == 0) {
                nombrePlato = tokenInner;
            } else if(valueNumber == 1) {
                if(stringIsValidFloat(tokenInner)) {
                    precioPlato = std::stof(tokenInner);
                    nuevoPlato = new PlatoComida(nombrePlato, precioPlato);
                    this->platosDisponibles.push_back(nuevoPlato);
                } else {
                    throw "Los precios del menu deben ser numeros con decimales";
                }
            } else {
                throw "Hay parametros demás en el menu";
            }
            valueNumber++;
            prevInner = posInner + 1;
        }
        prevOuter = posOuter + 1;
    }
    return  true;
}

PlatoComida Menu::eleccionRandom() {
    if(this->platosDisponibles.empty()) {
        throw "No se cargo ningun plato al Menu.";
    }
    srand((unsigned int)time(NULL));
    unsigned long seleccion = rand() % this->platosDisponibles.size();
    if(seleccion >= this->platosDisponibles.size()) {
        throw "Error de seleccion, evitando seg fault";
    }
    return PlatoComida(*this->platosDisponibles[seleccion]);
}

bool Menu::stringIsValidFloat(std::string str) {
    return true;
}