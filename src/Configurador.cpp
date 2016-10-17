//
// Created by mariano on 12/10/16.
//

#include "Configurador.h"
#include "Estructuras/SignalHandler.h"

Configurador::Configurador(ConfigLoader *config) {
    this->config = config;
}

void Configurador::crearEstructuras() {

    SignalHandler :: getInstance() ->registrarHandler(SIGINT,&sigint_handler);

    sem_entrada.crear(SEM_ENTRADA, 0, false);
    sem_recepcion.crear(SEM_RECEPCION, 0, false);
    sem_living.crear(SEM_LIVING, 0, false);
    sem_espera_luz.crear(SEM_ESPERA_LUZ,0,false);

    for (int i=0;i< config->getMesas();i++) {
        semaforosPedidoDeMesas[i] = Semaforo();
        semaforosPedidoDeMesas[i].crear(SEM_MESAS+i,0,false);
        semaforosSaldos[i] = Semaforo();
        semaforosSaldos[i].crear(config->getMesas()+SEM_SALDOS+i,0,false);
    }

    fifoRecepcionLectura.cargar(ARCHIVO_FIFO);
    fifoRecepcionEscritura.cargar(ARCHIVO_FIFO);
    fifoLivingLectura.cargar(ARCHIVO_FIFO_LIVING);
    fifoLivingEscritura.cargar(ARCHIVO_FIFO_LIVING);
    fifoMozosEscritura.cargar(ARCHIVO_FIFO_MOZOS);
    fifoMozosLectura.cargar(ARCHIVO_FIFO_MOZOS);
    fifoMozosCocineroEscritura.cargar(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    fifoMozosCocineroLectura.cargar(ARCHIVO_FIFO_MOZOS_Y_COCINERO);
    fifoCocineroEscritura.cargar(ARCHIVO_FIFO_COCINERO);
    fifoCocineroLectura.cargar(ARCHIVO_FIFO_COCINERO);

    menu = config->getMenu();

    recepcionistas.setCantidadDeRecepcionistas(config->getRecepcionistas());
    mozos.setCantidadDeMozos(config->getMozos());
    clientes.setCantidadDeClientes(config->getClientes());

    this->cagarGeneradorDeRecepcionistas();
    this->cargarGeneradorDeClientes();
    this->cargarGeneradorDeMozos();
    this->cargarCocinero();
    this->cargarGerente();

    mesas.setNumeroDeMesas(config->getMesas());

    mesas.armarMesas();
    administradorLiving.armarLiving();
    saldos.inicializarSaldoDeMesas(config->getMesas());
    caja.abrirCaja();

    this->cargarCorteDeLuz();

}

void Configurador::simular() {

    pid_recepcionistas = recepcionistas.cargarRecepcionistas(config->getMesas());

    pid_clientes = clientes.cargarClientes();

    pid_mozos = mozos.cargarMozos();

    pid_cocinero = cocinero.cargarCocinero();

    std::vector<pid_t> pids_clientes = clientes.getPidClientes();
    std::vector<pid_t> pids_recepcionistas = recepcionistas.getPidRecepcionistas();

    std::vector<pid_t> pids;

    pids.insert(pids.end(), pids_clientes.begin(), pids_clientes.end());
    pids.insert(pids.end(), pids_recepcionistas.begin(), pids_recepcionistas.end());
    pids.push_back(pid_mozos);
    pids.push_back(pid_cocinero);

    corteDeLuz.setPidProcesos(pids);

    pid_t pid_corteDeLuz = corteDeLuz.run();

    waitpid(pid_clientes,NULL,0);

    // eliminar semaforos
    sem_entrada.eliminar();
    sem_recepcion.eliminar();
    sem_living.eliminar();

    waitpid(pid_recepcionistas,NULL,0);

    waitpid(pid_mozos,NULL,0);

    waitpid(pid_cocinero,NULL,0);

    kill(pid_corteDeLuz,SIGINT);

    pid_t pid_gerente = gerente.run();

    waitpid(pid_gerente,NULL,0);

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

    sem_espera_luz.eliminar();

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
    clientes.setSigint_handler(&sigint_handler);

}

void Configurador::cagarGeneradorDeRecepcionistas() {

    recepcionistas.setFifoLivingEscritura(&fifoLivingEscritura);
    recepcionistas.setFifoRecepcionEscritura(&fifoRecepcionEscritura);
    recepcionistas.setSem_entrada(&sem_entrada);
    recepcionistas.setSem_recepcion(&sem_recepcion);
    recepcionistas.setSem_living(&sem_living);
    recepcionistas.setSigint_handler(&sigint_handler);
    recepcionistas.setSem_espera_luz(&sem_espera_luz);

}

void Configurador::cargarGeneradorDeMozos() {

    //this->sigint_handler.setAtenderSignal(&mozos);
    mozos.setSemaforosPedidoDeMesas(semaforosPedidoDeMesas);
    mozos.setFifoMozosLectura(&fifoMozosLectura);
    mozos.setFifoMozosCocineroLectura(&fifoMozosCocineroLectura);
    mozos.setFifoCocineroEscritura(&fifoCocineroEscritura);
    mozos.setMenu(&menu);
    mozos.setSemaforosSaldos(semaforosSaldos);
    mozos.setSigint_handler(&sigint_handler);
    mozos.setSem_espera_luz(&sem_espera_luz);

}

void Configurador::cargarCocinero(){
    cocinero.setFifoMozosCocineroEscritura(&fifoMozosCocineroEscritura);
    cocinero.setFifoCocineroLectura(&fifoCocineroLectura);
    cocinero.setMenu(&menu);
    cocinero.setSigint_handler(&sigint_handler);
    cocinero.setSem_espera_luz(&sem_espera_luz);
}

void Configurador::cargarGerente() {
    gerente.setAdministradorLiving(&administradorLiving);
    gerente.setCaja(&caja);
}

void Configurador::cargarCorteDeLuz() {

    corteDeLuz.setCaja(&caja);
    corteDeLuz.setMesas(&mesas);
    corteDeLuz.setSaldosDeMesa(&saldos);
    corteDeLuz.setAdministradorLiving(&administradorLiving);
    corteDeLuz.setSem_espera_luz(&sem_espera_luz);
    corteDeLuz.setCantidadDeProcesosActivar(config->getRecepcionistas());

}
