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
#include <sys/stat.h>

class ConfigLoader {
private:
    std::string confPath;
    std::ifstream fileStream;
    int cantMesas;
    int cantMozos;
    int cantRecepcionistas;
    Menu menuRestaurante;

    void setValueWithKey(std::string, std::string);

public:
    ConfigLoader(std::string);
    ~ConfigLoader();
    bool loadConfig();
    void closeFile();

    int getMozos();
    int getMesas();
    int getRecepcionistas();
    Menu getMenu();
};


#endif //TP1_CONFIGLOADER_H
