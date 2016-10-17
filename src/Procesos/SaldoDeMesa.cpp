//
// Created by mafv on 15/10/16.
//

#include "SaldoDeMesa.h"

SaldoDeMesa::SaldoDeMesa() {

}

void SaldoDeMesa::inicializarSaldoDeMesas(int numeroDeMesas) {

    this->numeroDeMesas = numeroDeMesas;

    for (int i = 0; i < this->numeroDeMesas ; ++i) {

        MemoriaCompartida<float> saldo;

        saldo.crear(MEMORIA_COMPARTIDA_SALDOS, i);

        saldo.escribir(0.0f);

        saldos.push_back(saldo);

    }

}

void SaldoDeMesa::agregarSaldo(int numeroDeMesa, float saldoAgregar) {

    LockFile lock(LOCK_SALDOS);

    lock.tomarLock();

    MemoriaCompartida<float> saldo;

    saldo.crear( MEMORIA_COMPARTIDA_SALDOS, numeroDeMesa );

    float saldoActual = saldo.leer();

    saldoActual += saldoAgregar;

    saldo.escribir(saldoActual);

    saldo.liberar();

    lock.liberarLock();

}

float SaldoDeMesa::obtenerSaldo(int numeroDeMesa) {

    LockFile lock(LOCK_SALDOS);

    lock.tomarLock();

    MemoriaCompartida<float> saldo;

    saldo.crear( MEMORIA_COMPARTIDA_SALDOS, numeroDeMesa );

    float saldoActual = saldo.leer();

    saldo.liberar();

    lock.liberarLock();

    return saldoActual;

}

void SaldoDeMesa::liberar() {

    for (int i = 0; i < numeroDeMesas ; ++i) {

        saldos[i].liberar();

    }

}

float SaldoDeMesa::anularSaldos() {

    LockFile lock(LOCK_SALDOS);

    lock.liberarLock();

    float saldosSinCobrar = 0.0f;

    for (int i = 0; i < numeroDeMesas ; ++i) {

        saldosSinCobrar += saldos[i].leer();

        saldos[i].escribir(0.0f);

    }

    return saldosSinCobrar;

}


void SaldoDeMesa::reiniciar(int numeroDeMesa) {

    LockFile lock(LOCK_SALDOS);

    lock.tomarLock();

    MemoriaCompartida<float> saldo;

    saldo.crear( MEMORIA_COMPARTIDA_SALDOS, numeroDeMesa );

    saldo.escribir(0.0f);

    saldo.liberar();

    lock.liberarLock();

}


