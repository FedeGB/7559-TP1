#include "Logger.h"

Logger* Logger :: instancia = NULL;
Archivo* Logger :: archivo = NULL;
LockFile* Logger :: lock = NULL;

Logger::Logger() {

}

Logger& Logger :: getInstance () {

    if ( instancia == NULL ){
        instancia = new Logger ();
        archivo = new Archivo("log-Restorrente");
        lock = new LockFile("/tmp/lockLogger");
    }

    return *instancia;
}

void Logger :: destruir () {

    if ( instancia != NULL ) {
        delete ( instancia );
        instancia = NULL;
    }

}

void Logger::log(const std::string &msg) {

    lock->tomarLock();

    std::string mensaje = this->obtenerFecha() + " " + msg;
    //std::cout << this->obtenerFecha() << " " << msg << std::endl;
    archivo->escribir(mensaje);

    lock->liberarLock();

}

std::string Logger::obtenerFecha() {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%d/%m/%y %H:%M:%S",timeinfo);

    return buffer;

}

Logger::~Logger() {

    delete archivo;
    delete lock;

}


