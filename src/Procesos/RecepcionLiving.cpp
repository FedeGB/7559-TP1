//
// Created by mafv on 10/10/16.
//

#include "RecepcionLiving.h"
#include "../Mesas.h"


RecepcionLiving::RecepcionLiving(Semaforo sem_living, FifoEscritura fifoLivingEscritura,int cantidadDeMesas)
        : sem_living(sem_living),
          fifoLivingEscritura(fifoLivingEscritura) {

    this->cantidadDeMesas = cantidadDeMesas;
}

void RecepcionLiving::_run(){


    fifoLivingEscritura.obtenerCopia();
    //fifoLivingEscritura.abrir();

    while (sem_living.p() > -1) {
        AdministradorLiving administradorLiving;
        Mesas mesas(cantidadDeMesas);

        if(administradorLiving.hayClientesEnElLiving()){

            int mesaLibre = mesas.obtenerMesaDesocupada();
            fifoLivingEscritura.escribir(&mesaLibre, sizeof(int));

            administradorLiving.sacarClienteDelLiving();

        }

    }

    fifoLivingEscritura.cerrar();

}
