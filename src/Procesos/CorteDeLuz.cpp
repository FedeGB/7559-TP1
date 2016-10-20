#include "CorteDeLuz.h"


CorteDeLuz::CorteDeLuz() {

}

void CorteDeLuz::_run() {

    this->sigint_handler->setAtenderSignal(this);

    while (true) {

        std::ios_base::sync_with_stdio(false);

        std::cout << "Presione enter para disparar el corte de luz: " << std::endl;

        std::cin.ignore(std::cin.rdbuf()->in_avail(), EOF);

        std::cin.get();

        for(auto pid : pid_procesos) {

            kill(pid,CORTE_DE_LUZ);

        }

        this->mesas->desocuparTodaLasMesas();
        float totalSinCobrar = saldos->anularSaldos();
        caja->agregarDineroSinCobrar(totalSinCobrar);
        administradorLiving->limpiarLiving();

        Logger::getInstance().log("Restableciendo la luz ... ");
        std::cout << "Restableciendo la luz ... " << std::endl;
        sleep(2);
        Logger::getInstance().log("luz restablecida ");
        std::cout << "luz restablecida " << std::endl;

        this->sem_espera_luz->v(this->cantidadDeProcesosActivar);

    }

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

void CorteDeLuz::setSigint_handler(SIGINT_Handler *sigint_handler) {
    CorteDeLuz::sigint_handler = sigint_handler;
}

void CorteDeLuz::atenderSenial() {
    exit(0);
}
