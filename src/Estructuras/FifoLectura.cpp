#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open ( nombre.c_str(),O_RDONLY );

	if (fd == -1) {

		std::string errMsg = std::string(std::string (strerror(errno)));
		throw "Fallo al abrir el fifo lectura: " + errMsg;

	}

}

ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) const {
	return read ( fd,buffer,buffsize );
}
