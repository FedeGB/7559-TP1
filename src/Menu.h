//
// Created by fedenote on 9/10/16.
//

#ifndef TP1_MENU_H
#define TP1_MENU_H


#include "Utils.h"
#include <vector>
#include "PlatoComida.h"
#include <stdlib.h>
#include <time.h>
#include <map>

class Menu {
private:
    //std::vector<PlatoComida> platosDisponibles;
    std::map<int,PlatoComida> platosDisponibles;

public:
    // Constructor que carga segun el archivo de configuracion el menu con los platos
    Menu();
    ~Menu();
    bool fill(std::string);
    //PlatoComida eleccionRandom();
    int getPlatoRandom();
    PlatoComida getPlato(int identificador);

};


#endif //TP1_MENU_H
