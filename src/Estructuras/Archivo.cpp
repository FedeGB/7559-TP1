#include "Archivo.h"

Archivo::Archivo(std::string ruta) {

    this->fd = open(ruta.c_str(), O_CREAT | O_RDWR, 0666);

    if (this->fd == -1) {

        std::string errMsg = std::string(std::string (strerror(errno)));
        throw "Fallo al abrir archivo: " + errMsg;

    }

}

void Archivo::escribir(std::string datos) {

    lseek(this->fd,0,SEEK_END);

    datos += "\n";

    ssize_t resultado = write(this->fd,static_cast<const void*>(datos.c_str()),datos.size());

    if (resultado == -1) {

        std::string errMsg = std::string(std::string (strerror(errno)));
        throw "Fallo al escribir en el archivo: " + errMsg;

    }

}

Archivo::~Archivo() {

    close(this->fd);

}
