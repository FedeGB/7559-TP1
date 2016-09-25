//
// Created by fedenote on 9/18/16.
//

#include "ConfigLoader.h"


ConfigLoader::ConfigLoader(std::string path) {
    cantMozos = 0;
    cantMesas = 0;
    cantRecepcionistas = 0;
    confPath = path;
}

ConfigLoader::~ConfigLoader() {
    this->closeFile();
}

int ConfigLoader::getMozos() {
    return cantMozos;
}

int ConfigLoader::getMesas(){
    return cantMesas;
}

int ConfigLoader::getRecepcionistas() {
    return cantRecepcionistas;
}

Menu ConfigLoader::getMenu() {
    return menuRestaurante;
}

void ConfigLoader::closeFile() {
    if(fileStream.is_open())
        fileStream.close();
}

bool ConfigLoader::loadConfig() {
    struct stat buffer;
    if(stat (this->confPath.c_str(), &buffer) != 0) {
        return false;
    }
    fileStream.open(this->confPath, std::ifstream::in);
    if(!fileStream.is_open()) {
        return  false;
    }
    std::string line;
    while(fileStream.good() && std::getline(fileStream, line)) {
        std::istringstream is_line(line);
        std::string clave;
        if( std::getline(is_line, clave, '=') ) {
            std::string valor;
            if( std::getline(is_line, valor) ) {
                setValueWithKey(clave, valor);
            }
        }
    }
    return true;
}

void ConfigLoader::setValueWithKey(std::string key, std::string value) {
    std::transform(key.begin(), key.end(),key.begin(), ::tolower);
    trim(key);
    trim(value);
    if(key.compare("mozos") == 0) {
        if(!stringIsInt(value)) {
            throw "Configuración invalida para mozos";
        }
        cantMozos = std::stoi(value);
    } else if(key.compare("recepcionistas") == 0) {
        if(!stringIsInt(value)) {
            throw "Configuración invalida para recepcionistas";
        }
        cantRecepcionistas = std::stoi(value);
    } else if(key.compare("mesas") == 0) {
        if(!stringIsInt(value)) {
            throw "Configuración invalida para mesas";
        }
        cantMesas = std::stoi(value);
    } else if(key.compare("menu") == 0) {
        if(!menuRestaurante.fill(value)) {
            throw "Configuración invalida para el menu";
        }
    }
}

