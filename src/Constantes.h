//
// Created by mafv on 09/10/16.
//

#ifndef TP1_CONSTANTES_H
#define TP1_CONSTANTES_H


#define CLIENTES 10
#define ARCHIVO_FIFO "/tmp/fifoRecepcion"
#define ARCHIVO_FIFO_LIVING "/tmp/fifoLiving"
#define LOCK_RECEPCION "/tmp/lockRecepcion"
#define LOCK_MESAS "/tmp/lockMesas"
#define LOCK_LIVING "/tmp/lockLiving"
#define LOCK_LIVING_ESPERA "/tmp/lockLivingEspera"
#define LOCK_CAJA "/tmp/lockCaja"
#define MEMORIA_COMPARTIDA_MESAS "/bin/bash"
#define MEMORIA_CLIENTES_LIVING "/bin/bash"
#define MEMORIA_DINERO_CAJA "/bin/bash"

struct asignarMesa {
    int mesa;
    bool living;
};


#endif //TP1_CONSTANTES_H
