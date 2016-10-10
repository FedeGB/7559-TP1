//
// Created by horacio on 9/19/16.
//

#include "Cliente.h"

Cliente::Cliente(int id, Semaforo sem_entrada, Semaforo sem_recepcion,Semaforo sem_living,FifoLectura fifoRecepcionLectura,FifoLectura fifoLivingLectura)
        : id(id),
          sem_entrada(sem_entrada),
          sem_recepcion(sem_recepcion),
          sem_living(sem_living),
          fifoRecepcionLectura(fifoRecepcionLectura),
          fifoLivingLectura(fifoLivingLectura){

    this->plata = id * 10 + 100;

}

void Cliente::_run() {
    Logger::getInstance().log("Creado cliente " + std::to_string(id) + ", con plata " + std::to_string(plata));

    sem_entrada.v(); // meto al cliente en la entrada, si no habia ninguno los recepcionistas estaban bloqueados aca esperando
    Logger::getInstance().log("cliente " + std::to_string(id) + " llego a la entrada");

    // espero a que me "recepcionen", si no hay ningun recepcionista bloquea aca
    sem_recepcion.p();

    this->esperarMesa();

}

void Cliente::esperarMesa() {

    struct asignarMesa mesaAsignada;
    char* buffer;

    buffer = new char[sizeof(mesaAsignada)];

    fifoRecepcionLectura.obtenerCopia();

    LockFile lock(LOCK_RECEPCION);

    lock.tomarLock();

    fifoRecepcionLectura.leer(buffer,sizeof(mesaAsignada));

    lock.liberarLock();

    fifoRecepcionLectura.cerrar();

    memcpy(&mesaAsignada,buffer,sizeof(mesaAsignada));

    delete buffer;

    Logger::getInstance().log("cliente " + std::to_string(id) + " fue atendido por un recepcionista");

    if (!mesaAsignada.living){

        this->mesaAsignada = mesaAsignada.mesa;

        this->pedirPlatos();

    } else {

        this->esperarEnElLiving();
    }

}

void Cliente::pedirPlatos() {

    Logger::getInstance().log("cliente " + std::to_string(id) + " le toco la mesa " + std::to_string(mesaAsignada));
    Logger::getInstance().log("cliente " + std::to_string(id) + " falta implementar comidas, me voy");

    //Sleep para que simule una espera antes de liberar la mesa
    sleep(2);

    Mesas mesa;

    mesa.desocuparMesa(mesaAsignada);

    sem_living.v();

}

void Cliente::esperarEnElLiving() {

    Logger::getInstance().log("cliente " + std::to_string(id) + " mesas ocupadas, voy al living ");

    AdministradorLiving administradorLiving;
    administradorLiving.agregarClienteAlLiving();

    char* buffer;

    buffer = new char[sizeof(int)];

    fifoLivingLectura.obtenerCopia();

    LockFile lock(LOCK_LIVING_ESPERA);

    lock.tomarLock();

    fifoLivingLectura.leer(buffer,sizeof(int));

    lock.liberarLock();

    fifoLivingLectura.cerrar();

    memcpy(&mesaAsignada,buffer,sizeof(int));

    delete buffer;

    Logger::getInstance().log("cliente " + std::to_string(id) + " se libero mesa, voy a comer ");

    this->pedirPlatos();

}
