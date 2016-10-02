#ifndef TP1_ARCHIVO_H
#define TP1_ARCHIVO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <cstring>
#include <errno.h>
#include <unistd.h>

class Archivo {

private:
    int fd;
public:

    Archivo(std::string ruta);

    void escribir(std::string datos);

    ~Archivo();

};


#endif //TP1_ARCHIVO_H
