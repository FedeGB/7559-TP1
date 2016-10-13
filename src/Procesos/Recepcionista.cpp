//
// Created by horacio on 9/24/16.
//

#include "Recepcionista.h"

Recepcionista::Recepcionista(std::string nombre, int cantidadDeMesas) : nombre(nombre) {

    this->cantidadDeMesas = cantidadDeMesas;

}

void Recepcionista::_run() {

    Logger::getInstance().log("Recepcionista " + nombre + " creado");

    fifoRecepcionEscritura->obtenerCopia();
    fifoRecepcionEscritura->abrir();

    while (sem_entrada->p() > -1) { //mientras haya clientes en la entrada (si no hay niguno bloque aca)

        //recibo a cliente:
        sem_recepcion->v();
        Logger::getInstance().log("Recepcionista " + nombre + " esta atendiendo a un cliente");

        sleep(5 + getRandomInt(1, 5)); // tiempo que tardo en atenderlo

        this->asignarMesa();

        Logger::getInstance().log("Recepcionista " + nombre + " termino de atender a un cliente");
    }

    fifoRecepcionEscritura->cerrar();

    delete fifoRecepcionEscritura;
    delete sem_entrada;
    delete sem_recepcion;

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
