#include "Esfinge.h"
#include <iostream>
#include <cstdlib>

Esfinge::Esfinge() : Entidad("Esfinge", 100, 12) {
    this -> contadorTurnos = 0;

    preguntas.push_back("Que camina en cuatro patas en la manana, en dos al mediodia y en tres en la tarde?\n1. El hombre\n2. El leon\n3. El aguila");
    respuestas.push_back(1);

    preguntas.push_back("Cuanto mas le quitas, mas grande se vuelve. Que es?\n1. Una deuda\n2. Un hueco\n3. Una sombra");
    respuestas.push_back(2);

    preguntas.push_back("Tiene dientes pero no muerde. Que es?\n1. Un serrucho dormido\n2. Una calavera\n3. Un peine");
    respuestas.push_back(3);
}

void Esfinge::atacar(Entidad& objetivo) {
    contadorTurnos++;

    if (contadorTurnos % 2 == 0) {
        bool acerto = lanzarAcertijo(objetivo);
        if (acerto == true) {
            std::cout << "Correcto! La Esfinge queda aturdida \n";
            congelar();
        }
        return;
    }

    if (rand() % 2 == 0) {
        std::cout << "La Esfinge te ataca con sus garras de leon \n";
        objetivo.recibirDanio(ataque, "normal");
    } else {
        std::cout << "La Esfinge se lanza en picada sobre ti \n";
        objetivo.recibirDanio(ataque * 2, "normal");
    }
}

bool Esfinge::lanzarAcertijo(Entidad& objetivo) {
    int i = rand() % preguntas.size();
    int respuesta;

    std::cout << "La Esfinge te lanza un acertijo: \n";
    std::cout << preguntas[i] << "\n";
    std::cout << "Tu respuesta: ";

    while (!(std::cin >> respuesta)) {
        std::cout << "Error: solo puedes ingresar el numero de la opcion (1, 2 o 3): ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    if (respuesta == respuestas[i]) {
        return true;
    }

    std::cout << "Incorrecto! La Esfinge te escupe fuego \n";
    objetivo.recibirDanio(ataque * 2, "fuego");
    return false;
}

int Esfinge::getRecompensaExp() const {
    return 150;
}
