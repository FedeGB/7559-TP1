#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "Logger.h"
#include "ConfigLoader.h"
#include "Cliente.h"
#include "Recepcionista.h"
#include "IDSemaforos.h"
#include "Semaforo.h"

using namespace std;

int main() {
    Logger::getInstance().log("Iniciando");
    ConfigLoader config("data.conf");
    if(!config.status()) {
        Logger::getInstance().log("No se pudo cargar el archivo de configuracion");
        return 1;
    }
    try {
        if (!config.loadConfig()) {
            Logger::getInstance().log("No se pudo cargar el archivo de configuracion");
        }
    } catch(const char* ex) {
        Logger::getInstance().log(ex);
        return 1;
    }
    Logger::getInstance().log("Se cargaron mesas: " + std::to_string(config.getMesas()));
    Logger::getInstance().log("Se cargaron mozos: " + std::to_string(config.getMozos()));
    Logger::getInstance().log("Se cargaron recep: " + std::to_string(config.getRecepcionistas()));

    Semaforo sem_entrada("/tmp/asdasdasd", SEM_ENTRADA, 0);
    sem_entrada.crear();

    Semaforo sem_recepcion("/tmp/as123d", SEM_RECEPCION, 0);
    sem_recepcion.crear();

    int clientes = 10;
    vector<pid_t> clientesPIDs;
    for(int i = 0; i < clientes; ++i){
        Cliente cliente(i,i*10+100);
        pid_t clientePID = cliente.run();
        clientesPIDs.push_back(clientePID);
    }

    Recepcionista recepcionista1("carlos1");
    pid_t recepcionista1PID = recepcionista1.run();
    //Recepcionista recepcionista2("carlos2");
    //pid_t recepcionista2PID = recepcionista2.run();
    //Recepcionista recepcionista3("carlos3");
    //pid_t recepcionista3PID = recepcionista3.run();

    sleep(30);

    return 0;
}