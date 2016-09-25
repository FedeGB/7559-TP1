#include <iostream>
#include <unistd.h>
#include "Logger.h"
#include "Cliente.h"
#include "Recepcionista.h"
#include "ConfigLoader.h"


using namespace std;

int main() {
    Logger::getInstance().log("Iniciando");
    ConfigLoader config("data.conf");
    try {
        if (!config.loadConfig()) {
            Logger::getInstance().log("No se pudo abrir el archivo de configuracion");
            return 1;
        }
    } catch(const char* ex) {
        Logger::getInstance().log(ex);
        config.closeFile();
        return 1;
    }
    Logger::getInstance().log("Se cargaron mesas: " + std::to_string(config.getMesas()));
    Logger::getInstance().log("Se cargaron mozos: " + std::to_string(config.getMozos()));
    Logger::getInstance().log("Se cargaron recep: " + std::to_string(config.getRecepcionistas()));
    Menu menu = config.getMenu();
    PlatoComida platoRandom = menu.eleccionRandom();
    Logger::getInstance().log("Se cargo el menu y un plato random es: " +
                                platoRandom.getNombre() + " con un precio de: " +
                              std::to_string(platoRandom.getPrecio()));

    //creacion de semaforos
    Semaforo sem_entrada(ARCHIVO_SEMAFOROS_ENTRADA, SEM_ENTRADA, 0);
    sem_entrada.crear();
    Semaforo sem_recepcion(ARCHIVO_SEMAFOROS_ENTRADA, SEM_RECEPCION, 0);
    sem_recepcion.crear();

    // creacion de clientes
    int clientes = 10;
    vector<pid_t> clientesPIDs;
    for(int i = 0; i < clientes; ++i){
        Cliente cliente(i,i*10+100);
        pid_t clientePID = cliente.run();
        clientesPIDs.push_back(clientePID);
    }

    // creacion de recepcionistas
    Recepcionista recepcionista1("carlos1");
    pid_t recepcionista1PID = recepcionista1.run();
    Recepcionista recepcionista2("carlos2");
    pid_t recepcionista2PID = recepcionista2.run();
    Recepcionista recepcionista3("carlos3");
    pid_t recepcionista3PID = recepcionista3.run();


    sleep(60); // TODO

    // eliminar semaforos
    sem_entrada.eliminar();
    sem_recepcion.eliminar();
    return 0;
}