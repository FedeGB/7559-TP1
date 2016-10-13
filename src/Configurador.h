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
#include "GeneradorMozos.h"
#include "ClientesPorComer.h"

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
    FifoEscritura *fifoMozosEscritura;
    FifoLectura *fifoMozosLectura;
    GeneradorRecepcionistas *recepcionistas;
    GeneradorClientes *clientes;
    GeneradorMozos *mozos;
    Mesas *mesas;
    AdministradorLiving *administradorLiving;
    ClientesPorComer clientesPorComer;
    pid_t pid_recepcionistas;
    pid_t pid_clientes;
    pid_t pid_mozos;

public:
    Configurador(ConfigLoader *config);
    void crearEstructuras();
    void destruirEstructuras();
    void simular();

private:
    void cargarGeneradorDeClientes();
    void cagarGeneradorDeRecepcionistas();
    void cargarGeneradorDeMozos();

};


#endif //TP1_CONFIGURADOR_H
