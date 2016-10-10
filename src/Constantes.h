//
// Created by mafv on 09/10/16.
//

#ifndef TP1_CONSTANTES_H
#define TP1_CONSTANTES_H


#define CLIENTES 4
#define ARCHIVO_FIFO "/tmp/fifoRecepcion"
#define LOCK_RECEPCION "/tmp/lockRecepcion"
#define LOCK_MESAS "/tmp/lockMesas"
#define MEMORIA_COMPARTIDA_MESAS "/bin/bash"

struct asignarMesa {
    int mesa;
    bool living;
};

struct Mesa {
    int numeroDeMesa;
    bool libre;
};

#endif //TP1_CONSTANTES_H
