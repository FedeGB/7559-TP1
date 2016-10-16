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
#include "Procesos/Cocinero.h"
#include "Procesos/SaldoDeMesa.h"

class Configurador {
private:
    ConfigLoader *config;
    Semaforo sem_entrada;
    Semaforo sem_recepcion;
    Semaforo sem_living;
    std::map<int,Semaforo> semaforosPedidoDeMesas;
    std::map<int,Semaforo> semaforosSaldos;
    FifoLectura fifoRecepcionLectura;
    FifoEscritura fifoRecepcionEscritura;
    FifoLectura fifoLivingLectura;
    FifoEscritura fifoLivingEscritura;
    FifoEscritura fifoMozosEscritura;
    FifoLectura fifoMozosLectura;
    FifoEscritura fifoMozosCocineroEscritura;
    FifoLectura fifoMozosCocineroLectura;
    FifoEscritura fifoCocineroEscritura;
    FifoLectura fifoCocineroLectura;
    GeneradorRecepcionistas recepcionistas;
    GeneradorClientes clientes;
    GeneradorMozos mozos;
    Cocinero cocinero;
    Mesas mesas;
    AdministradorLiving administradorLiving;
    Menu menu;
    SaldoDeMesa saldos;
    //ClientesPorComer clientesPorComer;
    pid_t pid_recepcionistas;
    pid_t pid_clientes;
    pid_t pid_mozos;
    pid_t pid_cocinero;

public:
    Configurador(ConfigLoader *config);
    void crearEstructuras();
    void destruirEstructuras();
    void simular();

private:
    void cargarGeneradorDeClientes();
    void cagarGeneradorDeRecepcionistas();
    void cargarGeneradorDeMozos();

    void cargarCocinero();
};


#endif //TP1_CONFIGURADOR_H
