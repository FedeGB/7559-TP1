#include "CorteDeLuz.h"

void CorteDeLuz::_run() {

    bool existio = false;

    while (!existio) {

        char t;
        std::cout << "Presione enter para disparar el corte de luz: " << std::endl;
        std::cin >> t;

        for(auto pid : pid_procesos) {

            kill(pid,CORTE_DE_LUZ);

        }

        this->mesas->desocuparTodaLasMesas();
        float totalSinCobrar = saldos->anularSaldos();
        caja->agregarDineroSinCobrar(totalSinCobrar);
        administradorLiving->limpiarLiving();

        Logger::getInstance().log("Reestableciendo la luz ... ");
        std::cout << "Reestableciendo la luz ... " << std::endl;
        sleep(2);
        Logger::getInstance().log("luz reestablecida ");
        std::cout << "luz reestablecida " << std::endl;

        this->sem_espera_luz->v(this->cantidadDeProcesosActivar);

        existio = true;

    }

    std::cout << "No se aceptan mas cortes de luz: " << std::endl;

}

void CorteDeLuz::setPidProcesos(std::vector<pid_t> pid_procesos) {

    this->pid_procesos = pid_procesos;

}

void CorteDeLuz::setMesas(Mesas *mesas){
    this->mesas = mesas;
}

void CorteDeLuz::setCaja(Caja *caja){
    this->caja = caja;
}

void CorteDeLuz::setSaldosDeMesa(SaldoDeMesa *saldos){
    this->saldos = saldos;
}

void CorteDeLuz::setAdministradorLiving(AdministradorLiving *administradorLiving) {
    CorteDeLuz::administradorLiving = administradorLiving;
}

void CorteDeLuz::setSem_espera_luz(Semaforo *sem_espera_luz) {
    this->sem_espera_luz = sem_espera_luz;
}

void CorteDeLuz::setCantidadDeProcesosActivar(int cantidad) {

    this->cantidadDeProcesosActivar = cantidad + 2;

}
