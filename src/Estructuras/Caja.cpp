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
    dinero.escribir(0.0f);
    dineroSinCobrar.crear(MEMORIA_DINERO_CAJA,'S');
    dineroSinCobrar.escribir(0.0f);
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

void Caja::agregarDineroSinCobrar(float deposito) {

    LockFile lock(LOCK_CAJA);
    lock.liberarLock();

    float dinero =dineroSinCobrar.leer();
    dinero += deposito;
    dineroSinCobrar.escribir(dinero);
}

void Caja::cerrarCaja() {
    dinero.liberar();
    dineroSinCobrar.liberar();
}

float Caja::consultarDineroPerdido() {
    LockFile lock(LOCK_CAJA);
    lock.tomarLock();
    dineroSinCobrar.crear(MEMORIA_DINERO_CAJA, 'S');
    float saldoActual = dineroSinCobrar.leer();
    dineroSinCobrar.liberar();
    lock.liberarLock();
    return saldoActual;
}
