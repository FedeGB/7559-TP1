//
// Created by fedenote on 9/25/16.
//

#include "Utils.h"

int getRandomInt(int min, int max){
    return rand()%(max-min + 1) + min;
}

void trim(std::string &str) {
    const std::string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return; // vacio

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    str = str.substr(strBegin, strRange);
}

bool stringIsInt(std::string str) {
    if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-')))
        return false;

    char * pointer ;
    strtol(str.c_str(), &pointer, 10) ;

    return (*pointer == 0) ;
}
