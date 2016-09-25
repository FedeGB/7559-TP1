#include <iostream>
#include <sys/types.h>
#include "Logger.h"
#include "ConfigLoader.h"
#include "Cliente.h"

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

    // ejemplo de creacion de procesos de cliente, el proceso hijo ejecuta lo que esta en _run y despues termina
    // obviamente tendria que haber un while(..) en el _run asi no termina de una, devuelve el pid del hijo al padre.
    int clientes = 10;
    vector<pid_t> clientesPIDs;
    for(int i = 0; i < clientes; ++i){
        Cliente cliente(i);
        pid_t clientePID = cliente.run();
        clientesPIDs.push_back(clientePID);
    }

    return 0;
}