
#ifndef TP1_GENERADORDECLIENTES_H
#define TP1_GENERADORDECLIENTES_H

#include "Estructuras/Semaforo.h"
#include "Procesos/Cliente.h"
#include "Estructuras/FifoLectura.h"
#include "Constantes.h"
#include "Estructuras/FifoEscritura.h"
#include "Menu.h"
#include "Estructuras/Pipe.h"
#include "Estructuras/SIGINT_Handler.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorClientes {
private:
    GeneradorClientes(int cantClientes);

    Pipe canal;
    std::vector<pid_t> pidClientes;
    FifoLectura *fifoRecepcionLectura;
    FifoLectura *fifoLivingLectura;
    FifoEscritura *fifoMozosEscritura;
    std::map<int,Semaforo> semaforosPedidoDeMesas;
    std::map<int,Semaforo> semaforosSaldos;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    Semaforo *sem_living;
    Menu *menu;
    int cantidadDeClientes;
    SIGINT_Handler *sigint_handler;

public:

    GeneradorClientes();

    pid_t cargarClientes();

    void setFifoRecepcionLectura(FifoLectura *fifoRecepcionLectura);

    void setFifoLivingLectura(FifoLectura *fifoLivingLectura);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setSem_living(Semaforo *sem_living);

    void setFifoMozosEscritura(FifoEscritura *fifoMozosEscritura);

    void setSemaforosPedidoDeMesas(const std::map<int, Semaforo> &semaforosPedidoDeMesas);

    void setMenu(Menu *menu);

    void setSemaforosSaldos(const std::map<int, Semaforo> &semaforosSaldos);

    void setCantidadDeClientes(int);

    std::vector<pid_t> getPidClientes();

    void setSigint_handler(SIGINT_Handler *sigint_handler);

private:
    void configurarCliente(Cliente &cliente);

};


#endif //TP1_GENERADORDECLIENTES_H
