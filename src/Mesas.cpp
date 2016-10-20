//
// Created by mafv on 10/10/16.
//

#include "Mesas.h"

Mesas::Mesas(int numeroDeMesas) {

    this->numeroDeMesas = numeroDeMesas;

}

Mesas::Mesas() {

}

void Mesas::setNumeroDeMesas(int numeroDeMesas) {

    this->numeroDeMesas = numeroDeMesas;

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

    if( this->verificarSiHayClientesEnElLiving() ) {

        return -1;

    }

    return this->buscarMesaLibre();


}

int Mesas::obtenerMesaDesocupada(){

    return this->buscarMesaLibre();

}

void Mesas::desocuparMesa(int numeroDeMesa) {

    LockFile lock(LOCK_MESAS);

    lock.tomarLock();

    MemoriaCompartida<bool> memoria;
    memoria.crear( MEMORIA_COMPARTIDA_MESAS, numeroDeMesa );

    memoria.escribir(true);

    memoria.liberar();

    lock.liberarLock();

}

void Mesas::desocuparTodaLasMesas() {

    LockFile lock(LOCK_MESAS);

    //Por si fue tomado antes del corte de luz
    lock.liberarLock();

    for (int i = 0; i < numeroDeMesas ; ++i) {
        memorias[i].escribir(true);
    }

}

Mesas::~Mesas() {

}

bool Mesas::verificarSiHayClientesEnElLiving() {

    AdministradorLiving administradorLiving;

    return administradorLiving.hayClientesEnElLiving();
}

int Mesas::buscarMesaLibre() {

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


