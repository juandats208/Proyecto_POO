#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Habitacion.h"
#include "MagoFuego.h"
#include "MagoHielo.h"
#include "MagoRayo.h"
#include "Kitsune.h"
#include "Esfinge.h"
#include "HidraDeLerna.h"

void mostrarVidas(Jugador* jugador, Entidad* enemigo) {
    std::cout << "\n[" << jugador -> getNombre() << ": " << jugador -> getVidaAct() << "/" << jugador -> getVidaMax() << "]";
    std::cout << "  [" << enemigo -> getNombre() << ": " << enemigo -> getVidaAct() << "/" << enemigo -> getVidaMax() << "]\n";
}

bool combatir(Jugador* jugador, Entidad* enemigo, Habitacion* actual) {
    std::cout << "\nAparece " << enemigo -> getNombre() << "!\n";

    while (jugador -> estaVivo() && enemigo -> estaVivo()) {

        // ----- Turno del jugador -----
        mostrarVidas(jugador, enemigo);
        jugador -> reducirRecarga();

        if (jugador -> procesarEstados() == true) {
            std::cout << "1. Ataque debil\n";
            std::cout << "2. Ataque fuerte\n";
            if (jugador -> puedeUsarEspecial()) {
                std::cout << "3. Habilidad especial\n";
            }
            if (jugador -> tieneObjetos()) {
                std::cout << "4. Usar objeto\n";
            }
            std::cout << "Opcion: ";
            int opcion;
            std::cin >> opcion;

            if (opcion == 1) {
                jugador -> atacar(*enemigo);
            } else if (opcion == 2) {
                jugador -> ataqueFuerte(*enemigo);
            } else if (opcion == 3 && jugador -> puedeUsarEspecial()) {
                jugador -> habilidadEspecial(*enemigo);
            } else if (opcion == 4 && jugador -> tieneObjetos()) {
                jugador -> mostrarInventario();
                std::cout << "Cual objeto? ";
                int indice;
                std::cin >> indice;
                jugador -> usarObjeto(indice);
            } else {
                std::cout << "Opcion invalida, pierdes el turno\n";
            }
        } else if (jugador -> estaVivo()) {
            std::cout << "No puedes actuar este turno\n";
        }

        if (enemigo -> estaVivo() == false) {
            break;
        }

        // ----- Turno del enemigo -----
        if (enemigo -> procesarEstados() == true) {
            enemigo -> atacar(*jugador);
        } else if (enemigo -> estaVivo()) {
            std::cout << enemigo -> getNombre() << " pierde su turno\n";
        }

        // Efecto de ambiente por turno (el calor de Tebas)
        if (actual -> getEfecto() == "calor") {
            actual -> aplicarEfecto(jugador);
        }
    }

    return jugador -> estaVivo();
}

int main() {
    srand(time(0));

    // ----- Crear el mapa -----
    Habitacion* santuario = new Habitacion("Santuario de los Mil Torii",
        "Un camino de cientos de arcos rojos que suben por una montana.",
        "proteccion");
    Habitacion* tebas = new Habitacion("Puertas de Tebas",
        "Un desierto ardiente frente a unas enormes puertas de piedra.",
        "calor");
    Habitacion* pantano = new Habitacion("Pantano de Lerna",
        "Un pantano de agua verde y espesa. Algo enorme se mueve bajo el agua.",
        "veneno");

    santuario -> agregarEnemigo(new Kitsune());
    santuario -> agregarObjeto(Objeto("Cola de Kitsune", "Sube tu ataque", "ataque", 8));

    tebas -> agregarEnemigo(new Esfinge());
    tebas -> agregarObjeto(Objeto("Antidoto de Hidra", "Quita el veneno", "antidoto", 0));

    pantano -> agregarEnemigo(new HidraDeLerna());

    santuario -> agregarSalida("adelante", tebas);
    tebas -> agregarSalida("atras", santuario);
    tebas -> agregarSalida("adelante", pantano);
    pantano -> agregarSalida("atras", tebas);

    // ----- Elegir mago -----
    std::string nombre;
    std::cout << "Como te llamas? ";
    std::cin >> nombre;

    std::cout << "Escoge tu mago:\n1. Fuego\n2. Hielo\n3. Rayo\nOpcion: ";
    int tipo;
    std::cin >> tipo;

    Jugador* jugador = nullptr;
    if (tipo == 2) {
        jugador = new MagoHielo(nombre);
    } else if (tipo == 3) {
        jugador = new MagoRayo(nombre);
    } else {
        jugador = new MagoFuego(nombre);
    }

    // ----- Ciclo principal -----
    Habitacion* actual = santuario;
    bool terminado = false;

    while (terminado == false) {
        actual -> mostrar();

        if (actual -> hayEnemigosVivos()) {
            bool gano = combatir(jugador, actual -> getEnemigo(), actual);

            if (gano == false) {
                std::cout << "\nHas muerto. Fin del juego.\n";
                terminado = true;
                break;
            }

            std::cout << "\nGanaste el combate!\n";
            actual -> desbloquear();

            std::vector<Objeto> encontrados = actual -> entregarObjetos();
            for (int i = 0; i < encontrados.size(); i++) {
                std::cout << "Encontraste: " << encontrados[i].getNombre() << "\n";
                jugador -> agregarObjeto(encontrados[i]);
            }

            if (actual == pantano) {
                std::cout << "\nDerrotaste a la Hidra de Lerna. Ganaste el juego!\n";
                terminado = true;
                break;
            }
        }

        std::cout << "\nA donde vas? (adelante / atras): ";
        std::string direccion;
        std::cin >> direccion;

        Habitacion* siguiente = actual -> getSalida(direccion);
        if (siguiente != nullptr) {
            actual = siguiente;
            if (actual -> getEfecto() == "veneno") {
                actual -> aplicarEfecto(jugador);
            }
        }
    }

    // ----- Liberar memoria -----
    delete jugador;
    delete santuario;
    delete tebas;
    delete pantano;

    return 0;
}
