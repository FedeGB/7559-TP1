#ifndef TP1_CORTEDELUZ_H
#define TP1_CORTEDELUZ_H


#include <vector>
#include "Proceso.h"
#include "Cliente.h"
#include "Recepcionista.h"
#include "Mozo.h"
#include "Cocinero.h"
#include "../Estructuras/Pipe.h"
#include "../Estructuras/Caja.h"
#include "SaldoDeMesa.h"
#include <sys/types.h>
#include <signal.h>

class CorteDeLuz : public Proceso {

private:

    std::vector<pid_t> pid_procesos;
    Caja *caja;
    Mesas *mesas;
    SaldoDeMesa *saldos;
    AdministradorLiving *administradorLiving;

public:
    void setPidProcesos(std::vector<pid_t> pid_procesos);

    void setMesas(Mesas *mesas);
    void setCaja(Caja *caja);
    void setSaldosDeMesa(SaldoDeMesa *saldos);
    void setAdministradorLiving(AdministradorLiving *administradorLiving);

private:

    void _run();

};


#endif //TP1_CORTEDELUZ_H
