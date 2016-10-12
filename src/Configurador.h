//
// Created by mariano on 12/10/16.
//

#ifndef TP1_CONFIGURADOR_H
#define TP1_CONFIGURADOR_H


#include <map>
#include "ConfigLoader.h"
#include "Estructuras/Semaforo.h"
#include "Estructuras/FifoLectura.h"
#include "Estructuras/FifoEscritura.h"
#include "GeneradorRecepcionistas.h"
#include "GeneradorClientes.h"

class Configurador {
private:
    ConfigLoader *config;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    Semaforo *sem_living;
    std::map<int,Semaforo*> semaforosPedidoDeMesas;
    FifoLectura *fifoRecepcionLectura;
    FifoEscritura *fifoRecepcionEscritura;
    FifoLectura *fifoLivingLectura;
    FifoEscritura *fifoLivingEscritura;
    GeneradorRecepcionistas *recepcionistas;
    GeneradorClientes *clientes;
    Mesas *mesas;
    AdministradorLiving *administradorLiving;
    pid_t pid_recepcionistas;
    pid_t pid_clientes;

public:
    Configurador(ConfigLoader *config);
    void crearEstructuras();
    void destruirEstructuras();
    void simular();

};


#endif //TP1_CONFIGURADOR_H
