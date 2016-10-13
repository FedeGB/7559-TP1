
#ifndef TP1_GENERADORDECLIENTES_H
#define TP1_GENERADORDECLIENTES_H

#include "Estructuras/Semaforo.h"
#include "Procesos/Cliente.h"
#include "Estructuras/FifoLectura.h"
#include "Constantes.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdexcept>

class GeneradorClientes {
private:
    FifoLectura *fifoRecepcionLectura;
    FifoLectura *fifoLivingLectura;
    Semaforo *sem_entrada;
    Semaforo *sem_recepcion;
    Semaforo *sem_living;

public:

    GeneradorClientes();

    pid_t cargarClientes();

    void setFifoRecepcionLectura(FifoLectura *fifoRecepcionLectura);

    void setFifoLivingLectura(FifoLectura *fifoLivingLectura);

    void setSem_entrada(Semaforo *sem_entrada);

    void setSem_recepcion(Semaforo *sem_recepcion);

    void setSem_living(Semaforo *sem_living);

private:
    void configurarCliente(Cliente &cliente);

};


#endif //TP1_GENERADORDECLIENTES_H
