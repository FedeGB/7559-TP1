#include "CorteDeLuz.h"

void CorteDeLuz::_run() {

    while (true) {

        char t;
        std::cout << "Presione enter para disparar el corte de luz: " << std::endl;
        std::cin >> t;

        for(auto pid : pid_procesos) {

            kill(pid,CORTE_DE_LUZ);

        }

        exit(0);

    }

}

void CorteDeLuz::setPidProcesos(std::vector<pid_t> pid_procesos) {

    this->pid_procesos = pid_procesos;

}
