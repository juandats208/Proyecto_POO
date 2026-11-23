#include "Kitsune.h"
#include <iostream>
#include <cstdlib>

Kitsune::Kitsune() : Entidad("Kitsune", 60, 8) {
    this -> probEsquivar = 20;
}

void Kitsune::atacar(Entidad& objetivo) {
    if (rand() % 2 == 0) {
        std::cout << "El Kitsune te da un coletazo \n";
        objetivo.recibirDanio(ataque, "normal");
    } else {
        std::cout << "El Kitsune lanza fuego de zorro (kitsunebi) \n";
        objetivo.recibirDanio(ataque + ataque / 2, "fuego");
    }
}

void Kitsune::recibirDanio(int cantidad, std::string tipo) {
    if (rand() % 100 < probEsquivar) {
        std::cout << "Era una ilusion! Tu ataque falla \n";
        return;
    }
    Entidad::recibirDanio(cantidad, tipo);
}

int Kitsune::getRecompensaExp() const {
    return 100;
}
