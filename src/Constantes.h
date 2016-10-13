//
// Created by mafv on 09/10/16.
//

#ifndef TP1_CONSTANTES_H
#define TP1_CONSTANTES_H


#define CLIENTES 2
#define ARCHIVO_FIFO "/tmp/fifoRecepcion"
#define ARCHIVO_FIFO_LIVING "/tmp/fifoLiving"
#define ARCHIVO_FIFO_MOZOS "/tmp/fifoMozos"
#define ARCHIVO_FIFO_COCINERO "/tmp/fifoCocinero"
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
#define LOCK_CLIENTES_POR_COMER "/tmp/clientesPorComer"

struct asignarMesa {
    int mesa;
    bool living;
};

//pedido: si es true es de un cliente, si es false es del cocinero
struct indicacionAlMozo {
    int numeroDeMesa;
    bool pedido;
};

struct ordenDeComida {
    int numeroDeMesa;
    int numeroPlato; // temporal
};


#endif //TP1_CONSTANTES_H
