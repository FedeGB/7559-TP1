#include "Fifo.h"

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {

	int resultado = mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );

	if (resultado == -1) {

		std::string errMsg = std::string(std::string (strerror(errno)));
		throw "Fallo al crear el fifo: " + errMsg;

	}

}

Fifo::~Fifo() {
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
