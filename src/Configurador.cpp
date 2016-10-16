//
// Created by mariano on 12/10/16.
//

#include "Configurador.h"

Configurador::Configurador(ConfigLoader *config) {
    this->config = config;
    //Logger::getInstance().log("MESAS: "+std::to_string(config->getMesas()));
}

void Configurador::crearEstructuras() {

    //sem_entrada = new Semaforo(SEM_ENTRADA, 0, false);
    sem_entrada.crear(SEM_ENTRADA, 0, false);
    //sem_recepcion = new Semaforo(SEM_RECEPCION, 0, false);
    sem_recepcion.crear(SEM_RECEPCION, 0, false);
    //sem_living = new Semaforo(SEM_LIVING, 0, false);
    sem_living.crear(SEM_LIVING, 0, false);

    for (int i=0;i< config->getMesas();i++) {
        semaforosPedidoDeMesas[i] = Semaforo();
        semaforosPedidoDeMesas[i].crear(SEM_MESAS+i,0,false);
        semaforosSaldos[i] = Semaforo();
        semaforosSaldos[i].crear(config->getMesas()+SEM_SALDOS+i,0,false);
    }

    //fifoRecepcionLectura = new FifoLectura(ARCHIVO_FIFO);
    fifoRecepcionLectura.cargar(ARCHIVO_FIFO);
    //fifoRecepcionEscritura = new FifoEscritura(ARCHIVO_FIFO);
    fifoRecepcionEscritura.cargar(ARCHIVO_FIFO);
    //fifoLivingLectura = new FifoLectura(ARCHIVO_FIFO_LIVING);
    fifoLivingLectura.cargar(ARCHIVO_FIFO_LIVING);
    //fifoLivingEscritura = new FifoEscritura(ARCHIVO_FIFO_LIVING);
    fifoLivingEscritura.cargar(ARCHIVO_FIFO_LIVING);
    //fifoMozosEscritura = new FifoEscritura(ARCHIVO_FIFO_MOZOS);
    fifoMozosEscritura.cargar(ARCHIVO_FIFO_MOZOS);
    //fifoMozosLectura = new FifoLectura(ARCHIVO_FIFO_MOZOS);
    fifoMozosLectura.cargar(ARCHIVO_FIFO_MOZOS);
    //fifoMozosCocineroEscritura = new FifoEscritura(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    fifoMozosCocineroEscritura.cargar(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    //fifoMozosCocineroLectura = new FifoLectura(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    fifoMozosCocineroLectura.cargar(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    //fifoCocineroEscritura = new FifoEscritura(ARCHIVO_FIFO_COCINERO);
    fifoCocineroEscritura.cargar(ARCHIVO_FIFO_COCINERO);
    //fifoCocineroLectura = new FifoLectura(ARCHIVO_FIFO_COCINERO);
    fifoCocineroLectura.cargar(ARCHIVO_FIFO_COCINERO);

    menu = config->getMenu();

    //recepcionistas = new GeneradorRecepcionistas(config->getRecepcionistas());
    recepcionistas.setCantidadDeRecepcionistas(config->getRecepcionistas());
    //clientes = new GeneradorClientes();
    //mozos = new GeneradorMozos(config->getMozos());
    mozos.setCantidadDeMozos(config->getMozos());
    clientes.setCantidadDeClientes(config->getClientes());
    //cocinero = new Cocinero();

    this->cagarGeneradorDeRecepcionistas();
    this->cargarGeneradorDeClientes();
    this->cargarGeneradorDeMozos();
    this->cargarCocinero();
    this->cargarGerente();

    //mesas = new Mesas(config->getMesas());
    mesas.setNumeroDeMesas(config->getMesas());
    //administradorLiving = new AdministradorLiving();

    //clientesPorComer.inicializar();
    mesas.armarMesas();
    administradorLiving.armarLiving();
    saldos.inicializarSaldoDeMesas(config->getMesas());
    caja.abrirCaja();

}

void Configurador::simular() {

    pid_recepcionistas = recepcionistas.cargarRecepcionistas(config->getMesas());

    pid_clientes = clientes.cargarClientes();

    pid_mozos = mozos.cargarMozos();

    pid_cocinero = cocinero.run();

    waitpid(pid_clientes,NULL,0);

    // eliminar semaforos
    sem_entrada.eliminar();
    sem_recepcion.eliminar();
    sem_living.eliminar();

    waitpid(pid_recepcionistas,NULL,0);

    //Falta ver como avisar a los mozos que terminaron
    waitpid(pid_mozos,NULL,0);

    waitpid(pid_cocinero,NULL,0);

    pid_t pid_gerente = gerente.run();

    waitpid(pid_gerente,NULL,0);

    //Logger::getInstance().log("Se cierra el dia con un total de "+std::to_string(caja.consultarDinero()));

}


void Configurador::destruirEstructuras() {

    fifoRecepcionEscritura.eliminar();
    fifoRecepcionLectura.eliminar();
    fifoLivingEscritura.eliminar();
    fifoLivingLectura.eliminar();
    fifoCocineroEscritura.eliminar();
    fifoCocineroLectura.eliminar();
    fifoMozosEscritura.eliminar();
    fifoMozosLectura.eliminar();
    fifoMozosCocineroEscritura.eliminar();
    fifoMozosCocineroLectura.eliminar();
    mesas.desarmarMesas();
    administradorLiving.desarmarLiving();
    saldos.liberar();
    caja.cerrarCaja();

    for (int i=0;i< config->getMesas();i++) {
        semaforosPedidoDeMesas[i].eliminar();
        semaforosSaldos[i].eliminar();
    }

}

void Configurador::cargarGeneradorDeClientes() {

    clientes.setFifoLivingLectura(&fifoLivingLectura);
    clientes.setFifoRecepcionLectura(&fifoRecepcionLectura);
    clientes.setFifoMozosEscritura(&fifoMozosEscritura);
    clientes.setSem_entrada(&sem_entrada);
    clientes.setSem_living(&sem_living);
    clientes.setSem_recepcion(&sem_recepcion);
    clientes.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    clientes.setMenu(&menu);
    clientes.setSemaforosSaldos(semaforosSaldos);

}

void Configurador::cagarGeneradorDeRecepcionistas() {

    recepcionistas.setFifoLivingEscritura(&fifoLivingEscritura);
    recepcionistas.setFifoRecepcionEscritura(&fifoRecepcionEscritura);
    recepcionistas.setSem_entrada(&sem_entrada);
    recepcionistas.setSem_recepcion(&sem_recepcion);
    recepcionistas.setSem_living(&sem_living);

}

void Configurador::cargarGeneradorDeMozos() {

    mozos.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    mozos.setFifoMozosLectura(&fifoMozosLectura);
    mozos.setFifoMozosCocineroLectura(&fifoMozosCocineroLectura);
    mozos.setFifoCocineroEscritura(&fifoCocineroEscritura);
    mozos.setMenu(&menu);
    mozos.setSemaforosSaldos(semaforosSaldos);

}

void Configurador::cargarCocinero(){
    cocinero.setFifoMozosCocineroEscritura(&fifoMozosCocineroEscritura);
    cocinero.setFifoCocineroLectura(&fifoCocineroLectura);
    cocinero.setMenu(&menu);
}

void Configurador::cargarGerente() {
    gerente.setAdministradorLiving(&administradorLiving);
    gerente.setCaja(&caja);
}
