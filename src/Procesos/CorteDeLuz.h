#ifndef TP1_CORTEDELUZ_H
#define TP1_CORTEDELUZ_H


#include <vector>
#include "Proceso.h"
#include "Cliente.h"
#include "Recepcionista.h"
#include "Mozo.h"
#include "Cocinero.h"
#include "../Estructuras/Pipe.h"
#include <sys/types.h>
#include <signal.h>

class CorteDeLuz : public Proceso {

private:

    std::vector<pid_t> pid_procesos;

public:
    void setPidProcesos(std::vector<pid_t> pid_procesos);


private:

    void _run();

};


#endif //TP1_CORTEDELUZ_H
