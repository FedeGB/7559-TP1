//
// Created by horacio on 9/19/16.
//

#include "Cliente.h"
#include "../ClientesPorComer.h"
#include "../Utils.h"
#include "SaldoDeMesa.h"


Cliente::Cliente(int id){

    this->cortesDeLuz = 0;
    this->id = id;
    this->plata = id * 10 + 100;
    this->platoPedidos = 0;
    this->estoyDentro = false;

}

void Cliente::_run() {

    Logger::getInstance().log("Creado cliente " + std::to_string(id) + ", con plata " + std::to_string(plata));

    sem_entrada->v(); // meto al cliente en la entrada, si no habia ninguno los recepcionistas estaban bloqueados aca esperando
    Logger::getInstance().log("cliente " + std::to_string(id) + " llego a la entrada");

    // espero a que me "recepcionen", si no hay ningun recepcionista bloquea aca
    sem_recepcion->p();

    this->estoyDentro = true;

    this->esperarMesa();

}

void Cliente::esperarMesa() {

    struct asignarMesa mesaAsignada;
    //char* buffer;

    //buffer = new char[sizeof(mesaAsignada)];

    fifoRecepcionLectura->obtenerCopia();

    LockFile lock(LOCK_RECEPCION);

    lock.tomarLock();

    fifoRecepcionLectura->leer(&mesaAsignada,sizeof(mesaAsignada));

    lock.liberarLock();

    fifoRecepcionLectura->cerrar();

   // memcpy(&mesaAsignada,buffer,sizeof(mesaAsignada));

    //delete buffer;

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
    //Logger::getInstance().log("cliente " + std::to_string(id) + " falta implementar comidas, me voy");

    //Sleep para que simule una espera antes de liberar la mesa

    ordenDeComida pedidoDePlato;

    pedidoDePlato.numeroDeMesa = mesaAsignada;
    pedidoDePlato.pedidoDeCuenta = false;
    pedidoDePlato.cortesDeLuz = this->cortesDeLuz;

    fifoMozosEscritura->obtenerCopia();

    //Realizo tres pedidos
    //Tendria que ser con los platos y la cantidad de plata
    do{

        pedidoDePlato.numeroPlato = menu->getPlatoRandom();

        Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " y voy a pedir el plato: "+menu->getPlato(pedidoDePlato.numeroPlato).getNombre());

        fifoMozosEscritura->escribir(&pedidoDePlato,sizeof(pedidoDePlato));

        semaforosPedidoDeMesas[mesaAsignada].p();

        Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " y voy a comer: "+menu->getPlato(pedidoDePlato.numeroPlato).getNombre());

        this->platoPedidos++;

    }while(this->pedirOtroPlato());

    this->pedirCuenta();

    fifoMozosEscritura->cerrar();

    Logger::getInstance().log("cliente " + std::to_string(id) + " no como mas, me voy");

    Mesas mesa;

    mesa.desocuparMesa(mesaAsignada);

    sem_living->v();

}

void Cliente::esperarEnElLiving() {

    Logger::getInstance().log("cliente " + std::to_string(id) + " mesas ocupadas, voy al living ");

    AdministradorLiving administradorLiving;

    administradorLiving.agregarClienteAlLiving();

    fifoLivingLectura->obtenerCopia();

    LockFile lock(LOCK_LIVING_ESPERA);

    lock.tomarLock();

    fifoLivingLectura->leer(&mesaAsignada,sizeof(int));

    lock.liberarLock();

    fifoLivingLectura->cerrar();

    Logger::getInstance().log("cliente " + std::to_string(id) + " se libero mesa, voy a comer ");

    this->pedirPlatos();

}

void Cliente::setSem_entrada(Semaforo *sem_entrada) {
    Cliente::sem_entrada = sem_entrada;
}

void Cliente::setSem_recepcion(Semaforo *sem_recepcion) {
    Cliente::sem_recepcion = sem_recepcion;
}

void Cliente::setSem_living(Semaforo *sem_living) {
    Cliente::sem_living = sem_living;
}

void Cliente::setFifoRecepcionLectura(FifoLectura *fifoRecepcionLectura) {
    Cliente::fifoRecepcionLectura = fifoRecepcionLectura;
}

void Cliente::setFifoLivingLectura(FifoLectura *fifoLivingLectura) {
    Cliente::fifoLivingLectura = fifoLivingLectura;
}

void Cliente::setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas) {
    Cliente::semaforosPedidoDeMesas = semaforosPedidoDeMesas;
}

void Cliente::setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura) {
    Cliente::fifoMozosEscritura = fifoMozosEscritura;
}

void Cliente::setMenu(Menu *menu) {
    Cliente::menu = menu;
}

bool Cliente::pedirOtroPlato() {

    if( this->platoPedidos > MAXIMO_PLATOS_A_PEDIR ) {

        return false;

    }

    srand(time(0));

    return ((1 + rand() % 2) == PIDO_PLATO) ;

}

void Cliente::pedirCuenta() {

    ordenDeComida orden;

    orden.pedidoDeCuenta = true;
    orden.numeroDeMesa = mesaAsignada;
    orden.cortesDeLuz = this->cortesDeLuz;

    Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " y voy a pedir la cuenta");

    fifoMozosEscritura->escribir(&orden,sizeof(orden));

    semaforosPedidoDeMesas[mesaAsignada].p();

    Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " y el mozo me entrego la cuenta");

    SaldoDeMesa saldo;

    float totalAPagar = saldo.obtenerSaldo(mesaAsignada);

    Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " y pago: "+std::to_string(totalAPagar));

    semaforosSaldos[mesaAsignada].v();

}

void Cliente::setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos) {
    Cliente::semaforosSaldos = semaforosSaldos;
}

void Cliente::atenderSenial() {

    if ( this->estoyDentro ) {
        LockFile lockLivingEspera(LOCK_LIVING_ESPERA);
        lockLivingEspera.liberarLock();
        fifoRecepcionLectura->cerrar();
        fifoRecepcionLectura->cerrar();
        fifoLivingLectura->cerrar();
        Logger::getInstance().log("Soy el cliente " + std::to_string(id) + " se corto la luz y me voy indignado");
        exit(0);
    } else {
        this->cortesDeLuz++;
        sem_recepcion->p();
    }

}
