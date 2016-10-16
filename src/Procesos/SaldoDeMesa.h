//
// Created by mafv on 15/10/16.
//

#ifndef TP1_SALDODEMESA_H
#define TP1_SALDODEMESA_H


#include <vector>
#include "../Estructuras/MemoriaCompartida.h"
#include "../Constantes.h"
#include "../Estructuras/LockFile.h"

class SaldoDeMesa {

private:

    int numeroDeMesas;

    std::vector< MemoriaCompartida<float> > saldos;

public:

    SaldoDeMesa();

    void inicializarSaldoDeMesas(int numeroDeMesas);

    void agregarSaldo(int numeroDeMesa,float saldoAgregar);

    float obtenerSaldo(int numeroDeMesa);

    void reiniciar(int numeroDeMesa);

    void liberar();

};


#endif //TP1_SALDODEMESA_H
