//
// Created by mafv on 09/10/16.
//

#ifndef TP1_CONSTANTES_H
#define TP1_CONSTANTES_H

#define PIDO_PLATO 1
#define MAXIMO_PLATOS_A_PEDIR 5
#define CLIENTES 4
#define ARCHIVO_FIFO "/tmp/fifoRecepcion"
#define ARCHIVO_FIFO_LIVING "/tmp/fifoLiving"
#define ARCHIVO_FIFO_MOZOS "/tmp/fifoMozos"
#define ARCHIVO_FIFO_COCINERO "/tmp/fifoCocinero"
#define ARCHIVO_FIFO_MOZOS_Y_COCINERO "/tmp/mozosYCocineros"
#define LOCK_RECEPCION "/tmp/lockRecepcion"
#define LOCK_MESAS "/tmp/lockMesas"
#define LOCK_LIVING "/tmp/lockLiving"
#define LOCK_LIVING_ESPERA "/tmp/lockLivingEspera"
#define LOCK_CAJA "/tmp/lockCaja"
#define LOCK_MOZOS "/tmp/lockMozos"
#define MEMORIA_COMPARTIDA_MESAS "/bin/bash"
#define MEMORIA_CLIENTES_LIVING "/bin/bash"
#define MEMORIA_CLIENTES_POR_COMER "/bin/bash"
#define MEMORIA_DINERO_CAJA "/bin/bash"
#define MEMORIA_COMPARTIDA_SALDOS "/bin/cat"
#define LOCK_CLIENTES_POR_COMER "/tmp/clientesPorComer"
#define LOCK_SALDOS "/tmp/lockSaldos"

struct asignarMesa {
    int mesa;
    bool living;
};


struct ordenDeComida {
    int numeroDeMesa;
    int numeroPlato; // temporal
    bool pedidoDeCuenta;
};


#endif //TP1_CONSTANTES_H
