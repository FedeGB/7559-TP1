//
// Created by mafv on 10/10/16.
//

#include "AdministradorLiving.h"


void AdministradorLiving::armarLiving() {

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');
    clientesEnElLiving.escribir(0);

    cantidadDeClientesEnElLiving.crear(MEMORIA_COMPARTIDA_CANTIDAD_LIVING,'C');
    cantidadDeClientesEnElLiving.escribir(0);

}

void AdministradorLiving::desarmarLiving() {

    clientesEnElLiving.liberar();

}

void AdministradorLiving::agregarClienteAlLiving() {

    LockFile lock(LOCK_LIVING);

    lock.tomarLock();

    clientesEnElLiving.crear(MEMORIA_CLIENTES_LIVING,'L');

    cantidadDeClientesEnElLiving.crear(MEMORIA_COMPARTIDA_CANTIDAD_LIVING,'C');

    int cantidadDeClientes = clientesEnElLiving.leer();
    cantidadDeClientes++;
    clientesEnElLiving.escribir(cantidadDeClientes);

    int clientesTotales = cantidadDeClientesEnElLiving.leer();
    clientesTotales++;
    cantidadDeClientesEnElLiving.escribir(clientesTotales);

    clientesEnElLiving.liberar();
    cantidadDeClientesEnElLiving.liberar();

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

int AdministradorLiving::clientesQueEsperaronEnElLiving() {

    cantidadDeClientesEnElLiving.crear(MEMORIA_COMPARTIDA_CANTIDAD_LIVING,'C');
    int clientesQueEsperaron = cantidadDeClientesEnElLiving.leer();
    cantidadDeClientesEnElLiving.liberar();

    return clientesQueEsperaron;
}
