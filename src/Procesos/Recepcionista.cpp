#include "Recepcionista.h"

Recepcionista::Recepcionista(std::string nombre, int cantidadDeMesas) : nombre(nombre) {

    this->cantidadDeMesas = cantidadDeMesas;

}

void Recepcionista::_run() {

    this->sigint_handler->setAtenderSignal(this);

    Logger::getInstance().log("Recepcionista " + nombre + " creada");

    fifoRecepcionEscritura->obtenerCopia();
    fifoRecepcionEscritura->abrir();

    //mientras haya clientes en la entrada (si no hay niguno bloque aca)
    while ( this->esperarClientes() ) {

        //recibo a cliente:
        sem_recepcion->v();
        Logger::getInstance().log("Recepcionista " + nombre + " esta atendiendo a un cliente");

        sleep(1 + getRandomInt(1, 5)); // tiempo que tardo en atenderlo

        this->asignarMesa();

        Logger::getInstance().log("Recepcionista " + nombre + " termino de atender a un cliente");
    }

    Logger::getInstance().log("Recepcionista " + nombre + " termino el dia, me retiro");

    fifoRecepcionEscritura->cerrar();

}

void Recepcionista::asignarMesa() {

    struct asignarMesa mesaAsignada;

    Mesas mesa(this->cantidadDeMesas);

    mesaAsignada.mesa = mesa.obtenerMesaLibre();

    mesaAsignada.living = (mesaAsignada.mesa == -1);

    fifoRecepcionEscritura->escribir(&mesaAsignada,sizeof(mesaAsignada));

    Logger::getInstance().log("Recepcionista " + nombre + " asigna mesa "+ std::to_string(mesaAsignada.mesa));

}

Recepcionista::~Recepcionista() {


}

void Recepcionista::setSem_entrada(Semaforo *sem_entrada) {
    Recepcionista::sem_entrada = sem_entrada;
}

void Recepcionista::setSem_recepcion(Semaforo *sem_recepcion) {
    Recepcionista::sem_recepcion = sem_recepcion;
}

void Recepcionista::setFifoRecepcionEscritura(FifoEscritura *fifoRecepcionEscritura) {
    Recepcionista::fifoRecepcionEscritura = fifoRecepcionEscritura;
}

void Recepcionista::setSigint_handler(SIGINT_Handler *sigint_handler) {
    Recepcionista::sigint_handler = sigint_handler;
}

void Recepcionista::setSem_espera_luz(Semaforo *sem_espera_luz) {

    this->sem_espera_luz = sem_espera_luz;

}

void Recepcionista::atenderSenial() {

    Logger::getInstance().log("Recepcionista " + nombre + " se corto la luz, espero que vuelva para atender mas clientes");

    this->sem_espera_luz->p();

    Logger::getInstance().log("Recepcionista " + nombre + " volvio la luz regreso al trabajo");

}

bool Recepcionista::esperarClientes() {

    int estado = 0;
    int error = 0;

    //do {

        estado = sem_entrada->p();

        error = errno;
        errno = 0;

//    }while (error == EXISTIO_CORTE_DE_LUZ);


    if(error == EXISTIO_CORTE_DE_LUZ){
        return true;
    }

    return estado != -1;

}
