#include "Archivo.h"

Archivo::Archivo(std::string ruta) {

    this->fd = open(ruta.c_str(), O_CREAT | O_RDWR, 0666);

    if (this->fd == -1) {

        std::cout << "Error al abrir el archivo: " << strerror(errno) << std::endl;

    }

}

void Archivo::escribir(std::string datos) {

    lseek(this->fd,0,SEEK_END);

    datos += "\n";

    ssize_t resultado = write(this->fd,static_cast<const void*>(datos.c_str()),datos.size());

    if (resultado == -1) {

        std::cout << "Error al escribir en el archivo: " << strerror(errno) << std::endl;

    }

}

Archivo::~Archivo() {

    close(this->fd);

}
