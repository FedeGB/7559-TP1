#include <iostream>
#include "Logger.h"
#include "Procesos/Cliente.h"
#include "ConfigLoader.h"
#include "Configurador.h"


using namespace std;

int main() {
    Logger::getInstance().log("Iniciando");
    ConfigLoader config("data.conf");
    try {
        if (!config.loadConfig()) {
            Logger::getInstance().log("No se pudo abrir el archivo de configuracion");
            return 1;
        }
    } catch (const char *ex) {
        Logger::getInstance().log(ex);
        config.closeFile();
        return 1;
    }
    Logger::getInstance().log("Se cargaron mesas: " + std::to_string(config.getMesas()));
    Logger::getInstance().log("Se cargaron mozos: " + std::to_string(config.getMozos()));
    Logger::getInstance().log("Se cargaron recepcionistas: " + std::to_string(config.getRecepcionistas()));
    Logger::getInstance().log("Se cargaron clientes: " + std::to_string(config.getClientes()));

    Configurador configurador(&config);
    configurador.crearEstructuras();
    configurador.simular();
    configurador.destruirEstructuras();

    Logger::getInstance().log("FIN");
    Logger::destruir();

    return 0;
}