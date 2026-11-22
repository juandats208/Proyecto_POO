#include "Entidad.h"
#include <iostream>

Entidad::Entidad(const std::string &nombre, int vida, int ataque) {
    this -> vidaAct = vida;
    this -> vidaMax = vida;
    this -> ataque = ataque;
    this -> nombre = nombre;
    this -> congelado = false;
    this -> turnosEnvenenado = 0;
    this -> turnosQuemado = 0;
}

Entidad::~Entidad() {

}

void Entidad::recibirDanio(int cantidad, std::string tipo) {
    if (cantidad <= 0) {
        std::cout << "El daño no puede ser negativo o igual a 0 \n";
        return;
    }
    vidaAct -= cantidad;
    if (vidaAct < 0) {
        vidaAct = 0;
    }
}

void Entidad::curar(int cantidad) {
    vidaAct += cantidad;
    if (vidaAct > vidaMax) {
        vidaAct = vidaMax;
    }
}

bool Entidad::estaVivo() const {
    if (vidaAct > 0) {
        return true;
    }
    return false;
}

void Entidad::congelar() {
    congelado = true;
}

void Entidad::quemar(int turnos) {
    turnosQuemado = turnos;
}

void Entidad::envenenar(int turnos) {
    turnosEnvenenado = turnos;
}

void Entidad::quitarEstados() {
    congelado = false;
    turnosQuemado = 0;
    turnosEnvenenado = 0;
}

bool Entidad::procesarEstados() {

    if (turnosQuemado > 0) {
        recibirDanio(5, "fuego");
        turnosQuemado--;
    }

    if (turnosEnvenenado > 0) {
        recibirDanio(3, "normal");
        turnosEnvenenado--;
    }

    if (vidaAct <= 0) {
        return false;
    }

    if (congelado == true) {
        congelado = false;
        return false;
    }

    return true;
}

void Entidad::subirAtaque(int cantidad) {
    if (cantidad <= 0) {
        std::cout << "La cantidad debe ser mayor que 0 \n";
    }
    ataque += cantidad;
}

int Entidad::getAtaque() const {
    return ataque;
}

std::string Entidad::getNombre() const {
    return nombre;
}

int Entidad::getVidaAct() const {
    return vidaAct;
}

int Entidad::getVidaMax() const {
    return vidaMax;
}
