//
// Created by fedenote on 9/10/16.
//

#ifndef TP1_PLATOCOMIDA_H
#define TP1_PLATOCOMIDA_H

#include <string>

class PlatoComida {
private:
    std::string nombre;
    float precio;
    int status;

public:
    static const int NUEVOPEDIDO = 0;
    static const int COCINANDO = 1;
    static const int ENTREGADO = 2;
    static const int COMIDO = 3;

    PlatoComida();
    PlatoComida(std::string, float);

    // Constructor de copia
    PlatoComida(const PlatoComida&);
    ~PlatoComida();
    float getPrecio();
    std::string getNombre();
    int getStatus();
    void changeStatus(int);

};


#endif //TP1_PLATOCOMIDA_H
