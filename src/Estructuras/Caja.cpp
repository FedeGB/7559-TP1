//
// Created by fedenote on 10/12/16.
//

#include "Caja.h"

Caja::Caja() {
}

Caja::~Caja() {
}

void Caja::abrirCaja() {
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    dinero.escribir(0);
}

float Caja::consultarDinero() {
    LockFile lock(LOCK_CAJA);
    lock.tomarLock();
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    float saldoActual = dinero.leer();
    dinero.liberar();
    lock.liberarLock();
    return saldoActual;
}

void Caja::agregarDinero(float deposito) {
    LockFile lock(LOCK_CAJA);
    lock.tomarLock();
    dinero.crear(MEMORIA_DINERO_CAJA, 'D');
    float cajaTotal = dinero.leer();
    cajaTotal += deposito;
    dinero.escribir(cajaTotal);
    dinero.liberar();
    lock.liberarLock();
}

void Caja::cerrarCaja() {
    dinero.liberar();
}

