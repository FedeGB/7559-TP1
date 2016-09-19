//
// Created by fedenote on 9/18/16.
//

#ifndef TP1_CONFIGLOADER_H
#define TP1_CONFIGLOADER_H

#include <string>
#include <fstream>
#include "Menu.h"
#include <sstream>
#include <algorithm>

class ConfigLoader {
private:
    std::ifstream fileStream;
    int cantMesas;
    int cantMozos;
    int cantRecepcionistas;
    bool statusGood;
    Menu menuRestaurante;

    void setValueWithKey(std::string, std::string);
    void trim(std::string &str);
    bool stringIsInt(std::string);

public:
    ConfigLoader(std::string);
    ~ConfigLoader();
    bool status();
    bool loadConfig();

    int getMozos();
    int getMesas();
    int getRecepcionistas();
    Menu getMenu();
};


#endif //TP1_CONFIGLOADER_H
