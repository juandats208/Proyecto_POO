#include "Objeto.h"
#include <iostream>

Objeto::Objeto(const std::string& nombre, const std::string& descripcion, const std::string& tipo, int valor) {
    this -> nombre = nombre;
    this -> descripcion = descripcion;
    this -> tipo = tipo;
    this -> valor = valor;
}

void Objeto::mostrar() const {
    std::cout << nombre << " (" << tipo << ")";
    if (tipo != "antidoto") {
        std::cout << " - valor: " << valor;
    }
    std::cout << "\n" << descripcion << "\n";
}

std::string Objeto::getNombre() const {
    return nombre;
}

std::string Objeto::getDescripcion() const {
    return descripcion;
}

std::string Objeto::getTipo() const {
    return tipo;
}

int Objeto::getValor() const {
    return valor;
}
