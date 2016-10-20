//
// Created by horacio on 9/19/16.
//
#include "Proceso.h"

Proceso::Proceso() {

}

Proceso::~Proceso() {

}

pid_t Proceso::run() {
    pid_t pid = fork();
    if (pid == -1) {
        throw std::runtime_error("Error al crear proceso");
    }

    if (pid == 0) {
        _run();
        exit(0);
    } else {
        return pid;
    }
}

