#include "MagoRayo.h"
#include <iostream>
#include <cstdlib>

MagoRayo::MagoRayo(const std::string& nombre)
    : Jugador(nombre, 80, 15) {
    this -> probCritico = 25;
}

void MagoRayo::atacar(Entidad& objetivo) {
    std::cout << nombre << " lanza una chispa a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque, "rayo");
}

void MagoRayo::ataqueFuerte(Entidad& objetivo) {
    int danio = ataque + rand() % 11;
    std::cout << nombre << " invoca un relampago sobre " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(danio, "rayo");
}

void MagoRayo::habilidadEspecial(Entidad& objetivo) {
    int danio = ataque;

    if (rand() % 100 < probCritico) {
        danio = danio * 2;
        std::cout << "Golpe critico! ";
    }

    std::cout << nombre << " lanza una tormenta sobre " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(danio, "rayo");
    recargaEspecial = 3;
}
