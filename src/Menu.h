//
// Created by fedenote on 9/10/16.
//

#ifndef TP1_MENU_H
#define TP1_MENU_H


#include <vector>
#include "PlatoComida.h"
#include <stdlib.h>
#include <time.h>

class Menu {
private:
    std::vector<PlatoComida> platosDisponibles;

public:
    // Constructor que carga segun el archivo de configuracion el menu con los platos
    Menu();
    bool fill(std::string);
    PlatoComida eleccionRandom();

};


#endif //TP1_MENU_H
