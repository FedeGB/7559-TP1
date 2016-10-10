//
// Created by horacio on 9/24/16.
//

#include "Recepcionista.h"

Recepcionista::Recepcionista(std::string nombre, Semaforo sem_entrada,Semaforo sem_recepcion,FifoEscritura fifoRecepcionEscritura,int cantidadDeMesas) : nombre(nombre), sem_entrada(sem_entrada),
                                                                               sem_recepcion(sem_recepcion),fifoRecepcionEscritura(fifoRecepcionEscritura) {

    this->cantidadDeMesas = cantidadDeMesas;

}

void Recepcionista::_run() {

    Logger::getInstance().log("Recepcionista " + nombre + " creado");

    fifoRecepcionEscritura.obtenerCopia();
    fifoRecepcionEscritura.abrir();

    while (sem_entrada.p() > -1) { //mientras haya clientes en la entrada (si no hay niguno bloque aca)

        //recibo a cliente:
        sem_recepcion.v();
        Logger::getInstance().log("Recepcionista " + nombre + " esta atendiendo a un cliente");

        sleep(5 + getRandomInt(1, 5)); // tiempo que tardo en atenderlo

        this->asignarMesa();

        Logger::getInstance().log("Recepcionista " + nombre + " termino de atender a un cliente");
    }

    fifoRecepcionEscritura.cerrar();

}

void Recepcionista::asignarMesa() {

    struct asignarMesa mesaAsignada;

    Mesas mesa(this->cantidadDeMesas);

    mesaAsignada.mesa = mesa.obtenerMesaLibre();

    mesaAsignada.living = (mesaAsignada.mesa == -1);

    fifoRecepcionEscritura.escribir(&mesaAsignada,sizeof(mesaAsignada));

    Logger::getInstance().log("Recepcionista " + nombre + " asigna mesa "+ std::to_string(mesaAsignada.mesa));

}

Recepcionista::~Recepcionista() {


}
