//
// Created by horacio on 9/24/16.
//


#include "Semaforo.h"


Semaforo :: Semaforo ( const std::string& nombre, const int projId, const int valorInicial )
        :valorInicial(valorInicial), nombre(nombre), projId(projId) {
}

Semaforo::~Semaforo() {
}

int Semaforo :: get() {
    key_t clave = ftok ( nombre.c_str(),projId );
    if(clave == -1) {
        throw std::runtime_error("error en semaforo en get ");
    }

    this->id = semget ( clave,1,0666 );
    if(this->id == -1) {
        throw std::runtime_error("error en semaforo en get ");
    }

    return this->id;
}

int Semaforo :: crear() {
    LockFile lock(this->nombre);
    lock.tomarLock();
    ///home/horacio/git/7559-TP1/asd0
    key_t clave = ftok ( nombre.c_str(),projId );
    if(clave == -1) {
        throw std::runtime_error("error en semaforo en crear ");
    }

    this->id = semget ( clave,1,0666 | IPC_CREAT ); // ver return
    if(this->id == -1) {
        throw std::runtime_error("error en semaforo en semget en crear ");
    }

    int res = this->inicializar ();

    lock.liberarLock();
    return res;
}

int Semaforo :: inicializar () const {

    union semnum {
        int val;
        struct semid_ds* buf;
        ushort* array;
    };

    semnum init;
    init.val = this->valorInicial;
    int resultado = semctl ( this->id,0,SETVAL,init );
    if(resultado == -1) {
        throw std::runtime_error("error en semaforo en inicializar");
    }
    return resultado;
}

int Semaforo ::decrementar() const {

    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = -1;	// restar 1 al semaforo
    operacion.sem_flg = 0;

    int resultado = semop ( this->id,&operacion,1 );
    if(resultado == -1) {
        throw std::runtime_error("error en semaforo en decrementar");
    }
    return resultado;
}

int Semaforo ::incrementar() const {

    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = 1;	// sumar 1 al semaforo
    operacion.sem_flg = 0;

    int resultado = semop ( this->id,&operacion,1 );
    if(resultado == -1) {
        throw std::runtime_error("error en semaforo en incrementar");
    }
    return resultado;
}


void Semaforo :: eliminar () const {
    int resultado = semctl ( this->id,0,IPC_RMID );
    if(resultado == -1) {
        throw std::runtime_error("error en semaforo en eliminar");
    }
    LockFile lock(this->nombre + std::to_string(projId));
    lock.clean();
}
