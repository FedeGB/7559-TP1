//
// Created by fedenote on 10/12/16.
//

#include "Caja.h"

Caja::Caja() {
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    dinero.escribir(0);
}

Caja::~Caja() {
    this->cerrarCaja();
}

float Caja::consultarDinero() {
    LockFile lock(LOCK_CAJA);
    lock.tomarLock();
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    float saldoActual = dinero.leer();
    lock.liberarLock();
    return saldoActual;
}

void Caja::agregarDinero(float deposito) {
    LockFile lock(LOCK_CAJA);
    lock.tomarLock();
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    dinero.escribir(deposito);
    lock.liberarLock();
}

void Caja::cerrarCaja() {
    dinero.liberar();
}
