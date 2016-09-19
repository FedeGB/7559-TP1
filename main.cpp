#include <iostream>
#include "Logger.h"
#include "ConfigLoader.h"

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
    return 0;
}