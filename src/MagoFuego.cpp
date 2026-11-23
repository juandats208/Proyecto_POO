#include "MagoFuego.h"
#include <iostream>

MagoFuego::MagoFuego(const std::string& nombre)
    : Jugador(nombre, 90, 12) {
    this -> turnosQuemadura = 3;
}

void MagoFuego::atacar(Entidad& objetivo) {
    std::cout << nombre << " lanza una llamarada a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque, "fuego");
}

void MagoFuego::ataqueFuerte(Entidad& objetivo) {
    std::cout << nombre << " lanza una bola de fuego a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque * 2, "fuego");
}

void MagoFuego::habilidadEspecial(Entidad& objetivo) {
    std::cout << "*** HABILIDAD ESPECIAL: LLAMAS ETERNAS ***\n";
    std::cout << nombre << " prende en llamas a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque, "fuego");
    objetivo.quemar(turnosQuemadura);
    std::cout << objetivo.getNombre() << " se quemara y perdera vida durante " << turnosQuemadura << " turnos!\n";
}