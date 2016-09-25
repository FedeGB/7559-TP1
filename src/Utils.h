//
// Created by root on 9/25/16.
//

#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#include <stdlib.h>

int getRandomInt(int min, int max){
    return rand()%(max-min + 1) + min;
}


#endif //TP1_UTILS_H
