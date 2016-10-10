//
// Created by mafv on 10/10/16.
//

#include "Mesas.h"
#include "Logger.h"

Mesas::Mesas(int numeroDeMesas) {

    this->numeroDeMesas = numeroDeMesas;

    //lock = new LockFile(LOCK_MESAS);

}

void Mesas::armarMesas() {

    for (int i = 0; i < numeroDeMesas ; ++i) {

        MemoriaCompartida<bool> memoria;

        memoria.crear(MEMORIA_COMPARTIDA_MESAS, i);

        memoria.escribir(true);

        memorias.push_back(memoria);

    }

}


void Mesas::desarmarMesas() {

    for (int i = 0; i < numeroDeMesas ; ++i) {

        memorias[i].liberar();

    }

}

int Mesas::obtenerMesaLibre() {

    int mesaAsignada = -1;

    LockFile lock(LOCK_MESAS);

    lock.tomarLock();

    for (int i = 0; i < numeroDeMesas ; ++i) {

        MemoriaCompartida<bool> memoria;
        memoria.crear( MEMORIA_COMPARTIDA_MESAS, i );

        if( memoria.leer() ) {

            memoria.escribir(false);

            mesaAsignada = i;

            memoria.liberar();

            break;

        }

        memoria.liberar();

    }

    lock.liberarLock();

    return mesaAsignada;

}


Mesas::~Mesas() {

    //delete lock;

}

