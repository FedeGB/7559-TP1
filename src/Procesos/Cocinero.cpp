#include "Cocinero.h"

Cocinero::Cocinero() {

    this->cortesDeLuz = 0;

}

Cocinero::Cocinero(int cortesDeLuz) {
    Logger::getInstance().log("Cocinero vuelve la luz, regreso al trabajo");
    this->cortesDeLuz = cortesDeLuz;
}


void Cocinero::_run() {

    this->sigint_handler->setAtenderSignal(this);

    fifoMozosCocineroEscritura->obtenerCopia();
    fifoCocineroLectura->obtenerCopia();

    while (true) {
        ordenDeComida orden;
        ssize_t leido = fifoCocineroLectura->leer(&orden, sizeof(orden));

        //Se cerro el fifo del cocinero
        if (leido == 0) {
            break;
        }

        if(orden.cortesDeLuz != this->cortesDeLuz){
            continue;
        }

        Logger::getInstance().log(
                "Cocinero recibio pedido de plato " + menu->getPlato(orden.numeroPlato).getNombre() + " de la mesa " +
                std::to_string(orden.numeroDeMesa) + " ,procede a cocinarlo");

        // Tiempo de cocinar
        sleep(5);

        enviarComidaAMozos(orden);
    }

    Logger::getInstance().log("COCINERO se las toma");

    fifoMozosCocineroEscritura->cerrar();
    fifoCocineroLectura->cerrar();

}

void Cocinero::enviarComidaAMozos(const ordenDeComida &orden) {

    Logger::getInstance().log(
            "Cocinero acaba de entregar a algun mozo el plato " + menu->getPlato(orden.numeroPlato).getNombre() +" para la mesa " + std::to_string(orden.numeroDeMesa));

    fifoMozosCocineroEscritura->escribir(&orden, sizeof(orden));
}

void Cocinero::setFifoMozosCocineroEscritura(FifoEscritura *fifoMozosCocineroEscritura) {
    this->fifoMozosCocineroEscritura = fifoMozosCocineroEscritura;
}

void Cocinero::setFifoCocineroLectura(FifoLectura *f) {
    this->fifoCocineroLectura = f;
}

void Cocinero::setMenu(Menu *menu) {
    Cocinero::menu = menu;
}

void Cocinero::setSigint_handler(SIGINT_Handler *sigint_handler) {

    this->sigint_handler = sigint_handler;

}

void Cocinero::atenderSenial() {

    fifoMozosCocineroEscritura->cerrar();
    fifoCocineroLectura->cerrar();

    Logger::getInstance().log("Cocinero se corto la luz espero a que vuelva");

    exit(0);

}

