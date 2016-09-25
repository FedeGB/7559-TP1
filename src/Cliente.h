//
// Created by horacio on 9/19/16.
//

#ifndef TP1_CLIENTE_H
#define TP1_CLIENTE_H


#include "Proceso.h"
#include <iostream>
#include <string>
#include <sys/types.h> 
#include "Logger.h"
#include "Semaforo.h"
#include "IDSemaforos.h"

class Cliente : public Proceso {
public:
    Cliente(int id,int plata);

private:
    int id;
    int plata;
    void _run();
};


#endif //TP1_CLIENTE_H
