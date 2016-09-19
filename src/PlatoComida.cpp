//
// Created by fedenote on 9/10/16.
//

#include "PlatoComida.h"

PlatoComida::PlatoComida() {
    this->nombre = "";
    this->precio = 0;
    this->status = PlatoComida::NUEVOPEDIDO;
}

PlatoComida::PlatoComida(std::string name, float price) {
    this->nombre = name;
    this->precio = price;
    this->status = PlatoComida::NUEVOPEDIDO;
}

PlatoComida::PlatoComida(const PlatoComida& original) {
    nombre = original.nombre;
    precio = original.precio;
    status = original.status;
}

float PlatoComida::getPrecio() {
    return this->precio;
}

std::string PlatoComida::getNombre() {
    return this->nombre;
}
int PlatoComida::getStatus() {
    return this->status;
}

void PlatoComida::changeStatus(int newStatus) {
    if(newStatus < this->status) {
        throw "Cambio de estado de " +
              std::to_string(this->status) + " a " +
              std::to_string(newStatus) + " es invalido.";
    }
    this->status = newStatus;
}

PlatoComida::~PlatoComida() {
}