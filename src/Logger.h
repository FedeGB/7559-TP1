#ifndef TP1_LOGGER_H
#define TP1_LOGGER_H

#include <string.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include "Estructuras/Archivo.h"
#include "Estructuras/LockFile.h"

class Logger {
private:

    static Logger* instancia;
    static Archivo* archivo;
    static LockFile* lock;

    Logger();

    ~Logger();

    std::string obtenerFecha();

public:
    //Logger(const Logger &) = delete;

    //Logger &operator=(const Logger &) = delete;

    static Logger &getInstance();
    static void destruir();

    void log(const std::string &msg);
};


#endif //TP1_LOGGER_H
