//
// Created by mafv on 13/10/16.
//

#include "ClientesPorComer.h"
#include "Constantes.h"
#include "Estructuras/LockFile.h"

ClientesPorComer::ClientesPorComer() {

    clientesQueFaltanComer.crear(MEMORIA_CLIENTES_POR_COMER,'C');

}

void ClientesPorComer::inicializar(){

    clientesQueFaltanComer.escribir(cantidadDeClientes);

}

void ClientesPorComer::descontarCliente(){

    LockFile lock(LOCK_CLIENTES_POR_COMER);

    lock.tomarLock();

    int clientes = clientesQueFaltanComer.leer();
    clientes--;
    clientesQueFaltanComer.escribir(clientes);

    lock.liberarLock();

}

void ClientesPorComer::liberar(){

    clientesQueFaltanComer.liberar();

}

bool ClientesPorComer::quedanClientes(){

    LockFile lock(LOCK_CLIENTES_POR_COMER);

    lock.tomarLock();

    int clientes = clientesQueFaltanComer.leer();


    lock.liberarLock();

    return (clientes != 0);

}

ClientesPorComer::ClientesPorComer(int cantClientesDisp) {
    clientesQueFaltanComer.crear(MEMORIA_CLIENTES_POR_COMER,'C');
    cantidadDeClientes = cantClientesDisp;
}

void ClientesPorComer::setCantidadDeClientesDisponibles(int cantClientesDisp) {
    cantidadDeClientes = cantClientesDisp;
}


