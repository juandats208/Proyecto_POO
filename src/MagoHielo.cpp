#include "MagoHielo.h"
#include <iostream>

MagoHielo::MagoHielo(const std::string& nombre)
    : Jugador(nombre, 100, 10) {
}

void MagoHielo::atacar(Entidad& objetivo) const {
    std::cout << nombre << " lanza un fragmento de hielo a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque, "hielo");
}

void MagoHielo::ataqueFuerte(Entidad& objetivo) {
    std::cout << nombre << " dispara una lanza de escarcha a " << objetivo.getNombre() << "\n";
    objetivo.recibirDanio(ataque + ataque / 2, "hielo");
}

void MagoHielo::habilidadEspecial(Entidad& objetivo) {
    std::cout << nombre << " congela a " << objetivo.getNombre() << "\n";
    objetivo.congelar();
    recargaEspecial = 3;
}
