#include <iostream>
#include <unistd.h>
#include "Logger.h"
#include "Procesos/Cliente.h"
#include "Procesos/Recepcionista.h"
#include "ConfigLoader.h"
#include "GeneradorRecepcionistas.h"
#include "GeneradorClientes.h"
#include "Estructuras/FifoLectura.h"
#include "Estructuras/FifoEscritura.h"
#include "Mesas.h"
#include "Estructuras/MemoriaCompartida2.h"
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

int main() {
    Logger::getInstance().log("Iniciando");
    ConfigLoader config("data.conf");
    try {
        if (!config.loadConfig()) {
            Logger::getInstance().log("No se pudo abrir el archivo de configuracion");
            return 1;
        }
    } catch (const char *ex) {
        Logger::getInstance().log(ex);
        config.closeFile();
        return 1;
    }
    Logger::getInstance().log("Se cargaron mesas: " + std::to_string(config.getMesas()));
    Logger::getInstance().log("Se cargaron mozos: " + std::to_string(config.getMozos()));
    Logger::getInstance().log("Se cargaron recep: " + std::to_string(config.getRecepcionistas()));
    Menu menu = config.getMenu();
    PlatoComida platoRandom = menu.eleccionRandom();
    Logger::getInstance().log("Se cargo el menu y un plato random es: " +
                              platoRandom.getNombre() + " con un precio de: " +
                              std::to_string(platoRandom.getPrecio()));

    Mesas mesas(config.getMesas());
    mesas.armarMesas();

    sleep(5);

    //creacion de semaforos
    Semaforo sem_entrada(SEM_ENTRADA, 0, false);
    Semaforo sem_recepcion(SEM_RECEPCION, 0, false);

    //creacion fifos recepcion
    FifoLectura fifoRecepcionLectura(ARCHIVO_FIFO);
    FifoEscritura fifoRecepcionEscritura(ARCHIVO_FIFO);

    GeneradorRecepcionistas recepcionistas(config.getRecepcionistas());
    pid_t pid_recepcionistas = recepcionistas.cargarRecepcionistas(sem_entrada, sem_recepcion,fifoRecepcionEscritura,config.getMesas());

    GeneradorClientes clientes;
    pid_t pid_clientes = clientes.cargarClientes(sem_entrada, sem_recepcion,fifoRecepcionLectura);

    waitpid(pid_clientes,NULL,0);

    // eliminar semaforos
    sem_entrada.eliminar();
    sem_recepcion.eliminar();

    waitpid(pid_recepcionistas,NULL,0);

    // eliminar fifos recepcion
    fifoRecepcionEscritura.eliminar();
    fifoRecepcionLectura.eliminar();

    mesas.desarmarMesas();

    Logger::destruir();
    return 0;
}