//
// Created by horacio on 9/24/16.
//

#ifndef TP1_SEMAFORO_H
#define TP1_SEMAFORO_H


#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;
    int valorInicial;
    std::string nombre;
    int projId;

    int inicializar() const;

public:
    Semaforo(const std::string &nombre, const int projId, const int valorInicial);

    ~Semaforo();

    int v() const;
    int p() const;

    int crear();

    int get();

    void eliminar() const;
};


#endif //TP1_SEMAFORO_H
