//
// Created by mafv on 10/10/16.
//

#include "AdministradorLiving.h"


void AdministradorLiving::armarLiving() {

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');
    clientesEnElLiving.escribir(0);

}

void AdministradorLiving::desarmarLiving() {

    clientesEnElLiving.liberar();

}

void AdministradorLiving::agregarClienteAlLiving() {

    LockFile lock(LOCK_LIVING);

    lock.tomarLock();

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');

    int cantidadDeClientes = clientesEnElLiving.leer();
    cantidadDeClientes++;
    clientesEnElLiving.escribir(cantidadDeClientes);

    clientesEnElLiving.liberar();

    lock.liberarLock();

}

void AdministradorLiving::sacarClienteDelLiving() {

    LockFile lock(LOCK_LIVING);

    lock.tomarLock();

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');

    int cantidadDeClientes = clientesEnElLiving.leer();
    cantidadDeClientes--;
    clientesEnElLiving.escribir(cantidadDeClientes);

    clientesEnElLiving.liberar();

    lock.liberarLock();

}

bool AdministradorLiving::hayClientesEnElLiving() {

    LockFile lock(LOCK_LIVING);

    lock.tomarLock();

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');

    int cantidadDeClientes = clientesEnElLiving.leer();

    clientesEnElLiving.liberar();

    lock.liberarLock();

    return (cantidadDeClientes != 0);

}
