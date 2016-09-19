//
// Created by horacio on 9/19/16.
//

#ifndef TP1_CLIENTE_H
#define TP1_CLIENTE_H


#include "Proceso.h"
#include <iostream>
#include <string>
#include <sys/types.h> 

class Cliente : public Proceso {
public:
    Cliente(int plata);

private:
    int plata;

    void _run();
};


#endif //TP1_CLIENTE_H
