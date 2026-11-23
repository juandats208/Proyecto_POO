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

int leerNumero() {
    int numero;
    while (!(std::cin >> numero)) {
        std::cout << "Error: solo puedes ingresar numeros. Intenta de nuevo: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    return numero;
}

void mostrarBienvenida() {
    std::cout << "==============================================\n";
    std::cout << "        BIENVENIDO A LA AVENTURA DEL MAGO     \n";
    std::cout << "==============================================\n\n";

    std::cout << "Eres un joven mago que debe atravesar tres lugares\n";
    std::cout << "llenos de criaturas legendarias. En cada habitacion\n";
    std::cout << "te espera un enemigo: si lo vences, la salida se abre\n";
    std::cout << "y puedes pasar a la siguiente. Si derrotas a la Hidra\n";
    std::cout << "de Lerna, ganas el juego.\n\n";

    std::cout << "--------------- LOS MAGOS ---------------\n\n";

    std::cout << "MAGO DE FUEGO  (Vida: 90 | Ataque: 12)\n";
    std::cout << "  El mas equilibrado de los tres.\n";
    std::cout << "  - Ataque debil: una pequena llamarada.\n";
    std::cout << "  - Ataque fuerte: bola de fuego, doble de dano.\n";
    std::cout << "  - Especial: prende en llamas al enemigo, que pierde\n";
    std::cout << "    vida durante 3 turnos.\n\n";

    std::cout << "MAGO DE HIELO  (Vida: 100 | Ataque: 10)\n";
    std::cout << "  El mas resistente, pero el que menos dano hace.\n";
    std::cout << "  No le afecta el calor del desierto.\n";
    std::cout << "  - Ataque debil: fragmento de hielo.\n";
    std::cout << "  - Ataque fuerte: lanza de escarcha.\n";
    std::cout << "  - Especial: congela al enemigo y le hace perder un turno.\n\n";

    std::cout << "MAGO DE RAYO  (Vida: 80 | Ataque: 15)\n";
    std::cout << "  El mas fragil, pero el que mas dano puede hacer.\n";
    std::cout << "  - Ataque debil: una chispa.\n";
    std::cout << "  - Ataque fuerte: relampago con dano variable.\n";
    std::cout << "  - Especial: tormenta con probabilidad de golpe critico\n";
    std::cout << "    (doble de dano).\n\n";

    std::cout << "COMO SE DESBLOQUEAN LOS ATAQUES:\n";
    std::cout << "  - Ataque fuerte: despues de 2 ataques debiles.\n";
    std::cout << "  - Habilidad especial: despues de 1 ataque debil y 1 fuerte.\n";
    std::cout << "  Combo ideal: debil -> debil -> fuerte -> ESPECIAL\n\n";

    std::cout << "-------------- LOS ENEMIGOS --------------\n\n";

    std::cout << "1. KITSUNE  - Santuario de los Mil Torii\n";
    std::cout << "  Zorro magico. Ataca con un coletazo o con fuego de zorro.\n";
    std::cout << "  Crea ilusiones: a veces tu ataque falla.\n\n";

    std::cout << "2. ESFINGE  - Puertas de Tebas\n";
    std::cout << "  Leon con alas de aguila. Ataca con garras o en picada.\n";
    std::cout << "  Cada 2 turnos te lanza un acertijo: si aciertas queda\n";
    std::cout << "  aturdida, si fallas te escupe fuego.\n";
    std::cout << "  El calor del desierto te quita vida cada turno.\n\n";

    std::cout << "3. HIDRA DE LERNA (jefe final)  - Pantano de Lerna\n";
    std::cout << "  Serpiente de varias cabezas. Te envenena o te muerde\n";
    std::cout << "  una vez por cada cabeza. Si no la golpeas con fuego\n";
    std::cout << "  o rayo, le crecen dos cabezas mas.\n";
    std::cout << "  El aire del pantano te envenena al entrar.\n\n";

    std::cout << "Mientras exploras puedes encontrar objetos que te curan,\n";
    std::cout << "suben tu ataque o quitan el veneno.\n\n";
}

void mostrarVidas(Jugador* jugador, Entidad* enemigo) {
    std::cout << "\n[" << jugador -> getNombre() << ": " << jugador -> getVidaAct() << "/" << jugador -> getVidaMax() << "]";
    std::cout << "  [" << enemigo -> getNombre() << ": " << enemigo -> getVidaAct() << "/" << enemigo -> getVidaMax() << "]\n";
}

bool combatir(Jugador* jugador, Entidad* enemigo, Habitacion* actual) {
    std::cout << "\nAparece " << enemigo -> getNombre() << "!\n";

    while (jugador -> estaVivo() && enemigo -> estaVivo()) {

        // ----- Turno del jugador -----
        mostrarVidas(jugador, enemigo);

        if (jugador -> procesarEstados() == true) {
            bool accionHecha = false;

            while (accionHecha == false) {
                std::cout << "1. Ataque debil\n";
                std::cout << "2. Ataque fuerte ";
                jugador -> mostrarProgresoFuerte();
                std::cout << "\n3. Habilidad especial ";
                jugador -> mostrarProgresoEspecial();
                std::cout << "\n";
                if (jugador -> tieneObjetos()) {
                    std::cout << "4. Usar objeto\n";
                }
                std::cout << "Opcion: ";
                int opcion = leerNumero();

                if (opcion == 1) {
                    jugador -> usarAtaqueDebil(*enemigo);
                    accionHecha = true;
                } else if (opcion == 2) {
                    if (jugador -> puedeUsarFuerte()) {
                        jugador -> usarAtaqueFuerte(*enemigo);
                        accionHecha = true;
                    } else {
                        std::cout << "El ataque fuerte esta bloqueado. Primero haz 2 ataques debiles.\n\n";
                    }
                } else if (opcion == 3) {
                    if (jugador -> puedeUsarEspecial()) {
                        jugador -> usarHabilidadEspecial(*enemigo);
                        accionHecha = true;
                    } else {
                        std::cout << "La habilidad especial esta bloqueada. Necesitas 1 ataque debil y 1 fuerte.\n\n";
                    }
                } else if (opcion == 4 && jugador -> tieneObjetos()) {
                    jugador -> mostrarInventario();
                    std::cout << "Escribe el numero del objeto: ";
                    int indice = leerNumero();
                    jugador -> usarObjeto(indice);
                    accionHecha = true;
                } else {
                    std::cout << "Opcion invalida. Escoge una de las opciones del menu.\n\n";
                }
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
        "Un camino de cientos de arcos rojos que suben por una montana.\nEstatuas de zorros de piedra te miran desde ambos lados.",
        "proteccion");
    Habitacion* tebas = new Habitacion("Puertas de Tebas",
        "Un desierto ardiente frente a unas enormes puertas de piedra.\nSobre ellas, una criatura con cuerpo de leon te observa en silencio.",
        "calor");
    Habitacion* pantano = new Habitacion("Pantano de Lerna",
        "Un pantano de agua verde y espesa. El aire huele a podrido.\nAlgo enorme se mueve bajo el agua.",
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

    // ----- Bienvenida y elegir mago -----
    mostrarBienvenida();

    std::string nombre;
    std::cout << "Como te llamas? ";
    std::getline(std::cin, nombre);

    std::cout << "\nEscoge tu mago:\n1. Fuego\n2. Hielo\n3. Rayo\nOpcion: ";
    int tipo = leerNumero();

    Jugador* jugador = nullptr;
    if (tipo == 2) {
        jugador = new MagoHielo(nombre);
    } else if (tipo == 3) {
        jugador = new MagoRayo(nombre);
    } else {
        jugador = new MagoFuego(nombre);
    }

    std::cout << "\nBuena suerte, " << nombre << ". Tu aventura comienza...\n";

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

            std::cout << "\n*** Felicidades! Superaste " << actual -> getNombre() << " ***\n";
            actual -> desbloquear();

            std::vector<Objeto> encontrados = actual -> entregarObjetos();
            for (int i = 0; i < encontrados.size(); i++) {
                std::cout << "Has obtenido: " << encontrados[i].getNombre() << "\n";
                jugador -> agregarObjeto(encontrados[i]);
            }

            if (actual == pantano) {
                std::cout << "\n==============================================\n";
                std::cout << "  Derrotaste a la Hidra de Lerna. GANASTE!\n";
                std::cout << "==============================================\n";
                terminado = true;
                break;
            }
        }

        // ----- Menu entre habitaciones -----
        bool decidido = false;
        while (decidido == false) {
            std::cout << "\nQue quieres hacer?\n";
            std::cout << "1. Ir a la siguiente habitacion\n";
            std::cout << "2. Volver a la habitacion anterior\n";
            std::cout << "3. Ver inventario\n";
            std::cout << "4. Usar un objeto\n";
            std::cout << "Opcion: ";
            int opcion = leerNumero();

            Habitacion* siguiente = nullptr;

            if (opcion == 1) {
                siguiente = actual -> getSalida("adelante");
            } else if (opcion == 2) {
                siguiente = actual -> getSalida("atras");
            } else if (opcion == 3) {
                jugador -> mostrarInventario();
            } else if (opcion == 4) {
                if (jugador -> tieneObjetos()) {
                    jugador -> mostrarInventario();
                    std::cout << "Escribe el numero del objeto: ";
                    jugador -> usarObjeto(leerNumero());
                } else {
                    std::cout << "No tienes objetos\n";
                }
            } else {
                std::cout << "Opcion invalida\n";
            }

            if (siguiente != nullptr) {
                actual = siguiente;
                decidido = true;
                if (actual -> getEfecto() == "veneno" && actual -> hayEnemigosVivos()) {
                    actual -> aplicarEfecto(jugador);
                }
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
