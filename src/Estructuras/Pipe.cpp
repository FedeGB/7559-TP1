#include "Pipe.h"

Pipe :: Pipe() : lectura(true), escritura(true) {
	pipe ( this->descriptores );
}

Pipe::~Pipe() {
}

void Pipe :: setearModo ( const int modo ) {
	int retorno;
	if ( modo == LECTURA ) {
		retorno = close ( this->descriptores[1] );
		this->escritura = false;

	} else if ( modo == ESCRITURA ) {
		retorno = close ( this->descriptores[0] );
		this->lectura = false;
	}

	if (retorno == -1) {

		std::string errMsg = std::string(std::string (strerror(errno)));
		throw "Fallo al cerrar el pipe: " + errMsg;

	}

}

ssize_t Pipe :: escribir ( const void* dato,int datoSize ) {
	if ( this->lectura == true ) {

		if( close ( this->descriptores[0] ) == -1 ){

			std::string errMsg = std::string(std::string (strerror(errno)));
			throw "Fallo al cerrar el pipe: " + errMsg;

		}

		this->lectura = false;

	}

	return write ( this->descriptores[1],dato,datoSize );
}

ssize_t Pipe :: leer ( void* buffer,const int buffSize ) {
	if ( this->escritura == true ) {

		if( close ( this->descriptores[1] ) == -1 ){

			std::string errMsg = std::string(std::string (strerror(errno)));
			throw "Fallo al cerrar el pipe: " + errMsg;

		}

		this->escritura = false;
	}

	return read ( this->descriptores[0],buffer,buffSize );
}

int Pipe :: getFdLectura () const {
	if ( this->lectura == true )
		return this->descriptores[0];
	else
		return -1;
}

int Pipe :: getFdEscritura () const {
	if ( this->escritura == true )
		return this->descriptores[1];
	else
		return -1;
}

void Pipe :: cerrar () {
	if ( this->lectura == true ) {

		if( close ( this->descriptores[0] ) == -1 ){

			std::string errMsg = std::string(std::string (strerror(errno)));
			throw "Fallo al cerrar el pipe: " + errMsg;

		}

		this->lectura = false;
	}

	if ( this->escritura == true ) {

		if( close ( this->descriptores[1] ) == -1 ){

			std::string errMsg = std::string(std::string (strerror(errno)));
			throw "Fallo al cerrar el pipe: " + errMsg;

		}
		
		this->escritura = false;
	}
}
