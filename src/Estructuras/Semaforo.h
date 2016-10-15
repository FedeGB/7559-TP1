#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;
    int valorInicial;
    bool undo;

    int inicializar() const;

public:
    Semaforo();
    Semaforo(int projID, const int valorInicial, bool undo);
    void crear(int projID, const int valorInicial, bool undo);
    ~Semaforo();

    int p() const; // decrementa
    int v() const; // incrementa
    void eliminar() const;
};

#endif /* SEMAFORO_H_ */
