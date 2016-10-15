#include "Semaforo.h"

Semaforo::Semaforo(int projID, const int valorInicial, bool undo) : valorInicial(valorInicial), undo(undo) {
    key_t clave = ftok("/bin/bash", projID);
    this->id = semget(clave, 1, 0666 | IPC_CREAT);

    this->inicializar();
}

Semaforo::~Semaforo() {
}

int Semaforo::inicializar() const {

    union semnum {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };

    semnum init;
    init.val = this->valorInicial;
    int resultado = semctl(this->id, 0, SETVAL, init);
    return resultado;
}

int Semaforo::p() const {

    struct sembuf operacion;

    operacion.sem_num = 0;    // numero de semaforo
    operacion.sem_op = -1;    // restar 1 al semaforo
    if (this->undo) {
        operacion.sem_flg = SEM_UNDO;
    } else {
        operacion.sem_flg = 0;
    }

    int resultado = semop(this->id, &operacion, 1);
    return resultado;
}

int Semaforo::v() const {

    struct sembuf operacion;

    operacion.sem_num = 0;    // numero de semaforo
    operacion.sem_op = 1;    // sumar 1 al semaforo
    if (this->undo) {
        operacion.sem_flg = SEM_UNDO;
    } else {
        operacion.sem_flg = 0;
    }
    int resultado = semop(this->id, &operacion, 1);
    return resultado;
}

void Semaforo::eliminar() const {
    semctl(this->id, 0, IPC_RMID);
}

void Semaforo::crear(int projID, const int valorInicial, bool undo) {

    this->valorInicial = valorInicial;
    this->undo = undo;
    key_t clave = ftok("/bin/bash", projID);
    this->id = semget(clave, 1, 0666 | IPC_CREAT);

    this->inicializar();
}

Semaforo::Semaforo() {

}
