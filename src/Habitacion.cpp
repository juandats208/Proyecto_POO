#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion(const std::string& nombre, const std::string& descripcion, const std::string& efecto) {
    this -> nombre = nombre;
    this -> descripcion = descripcion;
    this -> efectoAmbiente = efecto;
    this -> salidaBloqueada = false;
    this -> adelante = nullptr;
    this -> atras = nullptr;
}

Habitacion::~Habitacion() {
    for (int i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
}

void Habitacion::agregarEnemigo(Entidad* e) {
    enemigos.push_back(e);
    salidaBloqueada = true;
}

void Habitacion::agregarObjeto(Objeto obj) {
    objetos.push_back(obj);
}

void Habitacion::agregarSalida(const std::string& direccion, Habitacion* h) {
    if (direccion == "adelante") {
        adelante = h;
    } else if (direccion == "atras") {
        atras = h;
    }
}

void Habitacion::mostrar() const {
    std::cout << "\n=== " << nombre << " ===\n";
    std::cout << descripcion << "\n";

    std::cout << "Salidas: ";
    if (atras != nullptr) {
        std::cout << "atras (" << atras -> getNombre() << ")  ";
    }
    if (adelante != nullptr) {
        std::cout << "adelante (" << adelante -> getNombre() << ")";
    }
    std::cout << "\n";
}

bool Habitacion::hayEnemigosVivos() const {
    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] -> estaVivo()) {
            return true;
        }
    }
    return false;
}

Entidad* Habitacion::getEnemigo() const {
    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] -> estaVivo()) {
            return enemigos[i];
        }
    }
    return nullptr;
}

Habitacion* Habitacion::getSalida(const std::string& direccion) const {
    if (direccion == "atras" && atras != nullptr) {
        return atras;
    }
    if (direccion == "adelante" && adelante != nullptr) {
        if (salidaBloqueada == true) {
            std::cout << "La salida esta bloqueada \n";
            return nullptr;
        }
        return adelante;
    }
    std::cout << "No hay salida por ahi \n";
    return nullptr;
}

void Habitacion::desbloquear() {
    salidaBloqueada = false;
}

std::vector<Objeto> Habitacion::entregarObjetos() {
    std::vector<Objeto> copia = objetos;
    objetos.clear();
    return copia;
}

void Habitacion::aplicarEfecto(Jugador* j) {
    if (efectoAmbiente == "veneno") {
        std::cout << "El aire del pantano te envenena \n";
        j -> envenenar(3);
    } else if (efectoAmbiente == "calor") {
        if (j -> resisteCalor()) {
            std::cout << "Tu dominio del frio te protege del calor \n";
        } else {
            std::cout << "El calor del desierto te quema \n";
            j -> recibirDanio(3, "fuego");
        }
    }
}

std::string Habitacion::getNombre() const {
    return nombre;
}

std::string Habitacion::getEfecto() const {
    return efectoAmbiente;
}

void Habitacion::marcarSuperada() {
    for (int i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
    enemigos.clear();
    objetos.clear();
    salidaBloqueada = false;
}
