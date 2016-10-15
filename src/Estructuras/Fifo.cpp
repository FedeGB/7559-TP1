#include "Fifo.h"

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {

	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );

}

Fifo::Fifo() {

}

Fifo::~Fifo() {
}


void Fifo::cargar(const std::string nombre) {
	this->nombre = nombre;
	this->fd = -1;
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

void Fifo::cerrar() {

	if (close ( fd ) == -1) {

		std::string errMsg = std::string(std::string (strerror(errno)));
		throw "Fallo al cerrar el fifo: " + errMsg;

	}

	fd = -1;
}

void Fifo::eliminar() const {
	unlink ( nombre.c_str() );
}

void Fifo::obtenerCopia() {

	fd = dup(this->fd);

}


