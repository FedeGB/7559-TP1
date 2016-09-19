//
// Created by fedenote on 9/18/16.
//

#include <iostream>
#include "ConfigLoader.h"


ConfigLoader::ConfigLoader(std::string path) {
    cantMozos = 0;
    cantMesas = 0;
    cantRecepcionistas = 0;
    fileStream.open(path, std::ifstream::in);
    statusGood = fileStream.is_open();
}

ConfigLoader::~ConfigLoader() {
    if(fileStream.is_open()) fileStream.close();
}

bool ConfigLoader::status() {
    return statusGood;
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

bool ConfigLoader::loadConfig() {
    if(!statusGood) {
        return statusGood;
    }
    if(!fileStream.is_open()) {
        statusGood = false;
        return  statusGood;
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
        menuRestaurante.fill(value);
    }
}

void ConfigLoader::trim(std::string &str) {
    const std::string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    str = str.substr(strBegin, strRange);
}

bool ConfigLoader::stringIsInt(std::string str) {
    if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-')))
        return false;

    char * pointer ;
    strtol(str.c_str(), &pointer, 10) ;

    return (*pointer == 0) ;
}