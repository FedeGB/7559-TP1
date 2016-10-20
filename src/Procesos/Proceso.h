//
// Created by horacio on 9/19/16.
//

#ifndef TP1_PROCESO_H
#define TP1_PROCESO_H

#include <sys/types.h>
#include <stdexcept>
#include <unistd.h>

class Proceso {
public:
    Proceso();
    virtual ~Proceso();
    pid_t run();

protected:
    virtual void _run() = 0;
};

#endif //TP1_PROCESO_H
