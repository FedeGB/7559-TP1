//
// Created by fedenote on 9/10/16.
//

#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {
//    std::vector<PlatoComida*>::iterator it = this->platosDisponibles.begin();
//    while(it != this->platosDisponibles.end()) {
//        if((*it) != NULL) {
//            delete (*it);
//        }
//        it++;
//    }
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
    float precioPlato;
    int i = 0;
    while ((posOuter = str.find(delimiterMenu))) {
        tokenOuter = str.substr(prevOuter, posOuter);
        valueNumber = 0;
        std::string nombrePlato = "";
        prevInner = 0;
        while ((posInner = tokenOuter.find(delimiterPlato))) {
            tokenInner = tokenOuter.substr(prevInner, posInner);
            trim(tokenInner);
            if(valueNumber == 0) {
                nombrePlato = tokenInner;
            } else if(valueNumber == 1) {
                if(stringIsValidPrice(tokenInner)) {
                    precioPlato = std::stof(tokenInner);
                    PlatoComida nuevoPlato = PlatoComida(nombrePlato, precioPlato);
                    //this->platosDisponibles.push_back(nuevoPlato);
                    this->platosDisponibles[i] = nuevoPlato;
                    i++;
                } else {
                    throw "Los precios del menu deben ser numeros con decimales positivos";
                }
            } else {
                throw "Hay parametros demás en el menu";
            }
            if(posInner == std::string::npos) break;
            valueNumber++;
            tokenOuter = tokenOuter.substr(posInner + 1, tokenOuter.length() - posInner + 1);
        }
        if(posOuter == std::string::npos) break;
        str = str.substr(posOuter + 1, str.length() - posOuter + 1);
    }
    return  true;
}

/*PlatoComida Menu::eleccionRandom() {
    if(this->platosDisponibles.empty()) {
        throw "No se cargo ningun plato al Menu.";
    }
    srand((unsigned int)time(NULL));
    unsigned long seleccion = rand() % this->platosDisponibles.size();
    if(seleccion >= this->platosDisponibles.size()) {
        throw "Error de seleccion, evitando seg fault";
    }
    return PlatoComida(this->platosDisponibles[seleccion]);
}*/

int Menu::getPlatoRandom() {
    if(this->platosDisponibles.empty()) {
        throw "No se cargo ningun plato al Menu.";
    }
    srand((unsigned int)time(NULL));
    unsigned long seleccion = rand() % this->platosDisponibles.size();
    if(seleccion >= this->platosDisponibles.size()) {
        throw "Error de seleccion, evitando seg fault";
    }
    return seleccion;
}

PlatoComida Menu::getPlato(int identificador) {

    return this->platosDisponibles[identificador];

}
