#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre, int vida, int ataque)
    : Entidad(nombre, vida, ataque) {
    this -> recargaEspecial = 0;
}

void Jugador::atacar(Entidad& objetivo) {
    std::cout << nombre << " golpea con su baston a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque, "normal");
}

void Jugador::ataqueFuerte(Entidad& objetivo) {
    atacar(objetivo);
}

void Jugador::habilidadEspecial(Entidad& objetivo) {
    atacar(objetivo);
    recargaEspecial = 3;
}

bool Jugador::puedeUsarEspecial() const {
    if (recargaEspecial == 0) {
        return true;
    }
    return false;
}

void Jugador::reducirRecarga() {
    if (recargaEspecial > 0) {
        recargaEspecial--;
    }
}

void Jugador::agregarObjeto(Objeto obj) {
    inventario.push_back(obj);
}

void Jugador::mostrarInventario() const {
    if (inventario.size() == 0) {
        std::cout << "El inventario esta vacio \n";
        return;
    }
    for (int i = 0; i < inventario.size(); i++) {
        std::cout << i + 1 << ". " << inventario[i].getNombre() << "\n";
    }
}

void Jugador::usarObjeto(int indice) {
    int posicion = indice - 1;

    if (posicion < 0 || posicion >= inventario.size()) {
        std::cout << "Ese objeto no existe \n";
        return;
    }

    Objeto obj = inventario[posicion];

    if (obj.getTipo() == "curacion") {
        curar(obj.getValor());
    } else if (obj.getTipo() == "ataque") {
        subirAtaque(obj.getValor());
    } else if (obj.getTipo() == "antidoto") {
        quitarEstados();
    }

    std::cout << "Usaste " << obj.getNombre() << "\n";
    inventario.erase(inventario.begin() + posicion);
}

bool Jugador::tieneObjetos() const {
    if (inventario.size() > 0) {
        return true;
    }
    return false;
}
