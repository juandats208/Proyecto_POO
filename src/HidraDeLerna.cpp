#include "HidraDeLerna.h"
#include <iostream>
#include <cstdlib>

HidraDeLerna::HidraDeLerna() : Entidad("Hidra de Lerna", 150, 4) {
    this -> cabezas = 3;
    this -> maxCabezas = 9;
    this -> cabezasPorCrecer = 0;
}

void HidraDeLerna::atacar(Entidad& objetivo) {
    regenerar();

    if (rand() % 2 == 0) {
        std::cout << "La Hidra te muerde con veneno \n";
        objetivo.recibirDanio(ataque, "normal");
        objetivo.envenenar(3);
    } else {
        std::cout << "La Hidra ataca con sus " << cabezas << " cabezas \n";
        for (int i = 0; i < cabezas; i++) {
            objetivo.recibirDanio(ataque, "normal");
        }
    }
}

void HidraDeLerna::recibirDanio(int cantidad, std::string tipo) {
    Entidad::recibirDanio(cantidad, tipo);

    if (cabezas > 1) {
        cabezas--;
        std::cout << "Le cortaste una cabeza a la Hidra \n";
    }

    if (tipo != "fuego" && tipo != "rayo") {
        cabezasPorCrecer += 2;
        std::cout << "La herida no se cerro... van a crecer cabezas \n";
    } else {
        std::cout << "La herida se cauteriza \n";
    }
}

void HidraDeLerna::regenerar() {
    cabezas += cabezasPorCrecer;
    if (cabezas > maxCabezas) {
        cabezas = maxCabezas;
    }
    cabezasPorCrecer = 0;
}

int HidraDeLerna::getCabezas() const {
    return cabezas;
}

int HidraDeLerna::getRecompensaExp() const {
    return 200;
}
