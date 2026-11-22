#include "Habitacion.h"
#include "MagoHielo.h"
#include <iostream>

Habitacion::Habitacion(const std::string& nombre, const std::string& descripcion, const std::string& efecto) {
    this -> nombre = nombre;
    this -> descripcion = descripcion;
    this -> efectoAmbiente = efecto;
    this -> salidaBloqueada = false;
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
    salidas[direccion] = h;
}

void Habitacion::mostrar() const {
    std::cout << "\n=== " << nombre << " ===\n";
    std::cout << descripcion << "\n";

    std::cout << "Salidas: ";
    for (auto par : salidas) {
        std::cout << par.first << " (" << par.second -> getNombre() << ")  ";
    }
    std::cout << "
";
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
    if (salidaBloqueada == true) {
        std::cout << "La salida esta bloqueada 
";
        return nullptr;
    }
    if (salidas.count(direccion) == 0) {
        std::cout << "No hay salida por ahi 
";
        return nullptr;
    }
    return salidas.at(direccion);
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
        if (dynamic_cast<MagoHielo*>(j) != nullptr) {
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
