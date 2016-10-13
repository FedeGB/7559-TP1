//
// Created by mariano on 12/10/16.
//

#include "Configurador.h"
#include "Logger.h"

Configurador::Configurador(ConfigLoader *config) {
    this->config = config;
    Logger::getInstance().log("MESAS: "+std::to_string(config->getMesas()));
}

void Configurador::crearEstructuras() {

    sem_entrada = new Semaforo(SEM_ENTRADA, 0, false);
    sem_recepcion = new Semaforo(SEM_RECEPCION, 0, false);
    sem_living = new Semaforo(SEM_LIVING, 0, false);

    for (int i=0;i< config->getMesas();i++) {
        semaforosPedidoDeMesas[i] = new Semaforo(SEM_MESAS+i,0,false);
    }

    fifoRecepcionLectura = new FifoLectura(ARCHIVO_FIFO);
    fifoRecepcionEscritura = new FifoEscritura(ARCHIVO_FIFO);
    fifoLivingLectura = new FifoLectura(ARCHIVO_FIFO_LIVING);
    fifoLivingEscritura = new FifoEscritura(ARCHIVO_FIFO_LIVING);
    fifoMozosEscritura = new FifoEscritura(ARCHIVO_FIFO_MOZOS);
    fifoMozosLectura = new FifoLectura(ARCHIVO_FIFO_MOZOS);

    recepcionistas = new GeneradorRecepcionistas(config->getRecepcionistas());
    clientes = new GeneradorClientes();
    mozos = new GeneradorMozos(config->getMozos());

    this->cagarGeneradorDeRecepcionistas();
    this->cargarGeneradorDeClientes();
    this->cargarGeneradorDeMozos();

    mesas = new Mesas(config->getMesas());
    administradorLiving = new AdministradorLiving();

    clientesPorComer.inicializar();
    mesas->armarMesas();
    administradorLiving->armarLiving();

}

void Configurador::simular() {

    pid_recepcionistas = recepcionistas->cargarRecepcionistas(config->getMesas());

    pid_clientes = clientes->cargarClientes();

    pid_mozos = mozos->cargarMozos();

    waitpid(pid_clientes,NULL,0);

    // eliminar semaforos
    sem_entrada->eliminar();
    sem_recepcion->eliminar();
    sem_living->eliminar();

    waitpid(pid_recepcionistas,NULL,0);

    //Falta ver como avisar a los mozos que terminaron
    waitpid(pid_mozos,NULL,0);

}


void Configurador::destruirEstructuras() {

    fifoRecepcionEscritura->eliminar();
    fifoRecepcionLectura->eliminar();
    fifoLivingEscritura->eliminar();
    fifoLivingLectura->eliminar();
    mesas->desarmarMesas();
    administradorLiving->desarmarLiving();
    clientesPorComer.liberar();

    for(auto const &ent1 : semaforosPedidoDeMesas) {

        ent1.second->eliminar();
        delete ent1.second;

    }

    delete sem_entrada;
    delete sem_recepcion;
    delete sem_living;
    delete fifoLivingEscritura;
    delete fifoLivingLectura;
    delete fifoRecepcionEscritura;
    delete fifoRecepcionLectura;
    delete fifoMozosEscritura;
    delete fifoMozosLectura;
    delete recepcionistas;
    delete clientes;
    delete mesas;
    delete administradorLiving;

}

void Configurador::cargarGeneradorDeClientes() {

    clientes->setFifoLivingLectura(fifoLivingLectura);
    clientes->setFifoRecepcionLectura(fifoRecepcionLectura);
    clientes->setFifoMozosEscritura(fifoMozosEscritura);
    clientes->setSem_entrada(sem_entrada);
    clientes->setSem_living(sem_living);
    clientes->setSem_recepcion(sem_recepcion);
    clientes->setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);

}

void Configurador::cagarGeneradorDeRecepcionistas() {

    recepcionistas->setFifoLivingEscritura(fifoLivingEscritura);
    recepcionistas->setFifoRecepcionEscritura(fifoRecepcionEscritura);
    recepcionistas->setSem_entrada(sem_entrada);
    recepcionistas->setSem_recepcion(sem_recepcion);
    recepcionistas->setSem_living(sem_living);

}

void Configurador::cargarGeneradorDeMozos() {

    mozos->setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    mozos->setFifoMozosLectura(fifoMozosLectura);

}
