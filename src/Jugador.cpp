#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre, int vida, int ataque)
    : Entidad(nombre, vida, ataque) {
    this -> debilesSeguidos = 0;
    this -> usoDebil = false;
    this -> usoFuerte = false;
    this -> nivel = 1;
    this -> experiencia = 0;
    this -> expParaSubir = 100;
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
}

void Jugador::usarAtaqueDebil(Entidad& objetivo) {
    bool especialAntes = puedeUsarEspecial();

    atacar(objetivo);
    debilesSeguidos++;
    usoDebil = true;

    if (debilesSeguidos == 2) {
        std::cout << "*** Ataque fuerte desbloqueado! ***\n";
    }
    if (especialAntes == false && puedeUsarEspecial() == true) {
        std::cout << "*** Habilidad especial desbloqueada! ***\n";
    }
}

void Jugador::usarAtaqueFuerte(Entidad& objetivo) {
    bool especialAntes = puedeUsarEspecial();

    ataqueFuerte(objetivo);
    debilesSeguidos = 0;
    usoFuerte = true;

    if (especialAntes == false && puedeUsarEspecial() == true) {
        std::cout << "*** Habilidad especial desbloqueada! ***\n";
    }
}

void Jugador::usarHabilidadEspecial(Entidad& objetivo) {
    habilidadEspecial(objetivo);
    usoDebil = false;
    usoFuerte = false;
}

bool Jugador::puedeUsarFuerte() const {
    if (debilesSeguidos >= 2) {
        return true;
    }
    return false;
}

bool Jugador::puedeUsarEspecial() const {
    if (usoDebil == true && usoFuerte == true) {
        return true;
    }
    return false;
}

void Jugador::mostrarProgresoFuerte() const {
    if (puedeUsarFuerte()) {
        std::cout << "(listo!)";
    } else {
        int faltan = 2 - debilesSeguidos;
        std::cout << "(bloqueado: haz " << faltan << " ataque(s) debil(es) mas)";
    }
}

void Jugador::mostrarProgresoEspecial() const {
    if (puedeUsarEspecial()) {
        std::cout << "(lista!)";
    } else if (usoDebil == false && usoFuerte == false) {
        std::cout << "(bloqueada: haz 1 ataque debil y 1 fuerte)";
    } else if (usoDebil == false) {
        std::cout << "(bloqueada: te falta 1 ataque debil)";
    } else {
        std::cout << "(bloqueada: te falta 1 ataque fuerte)";
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

    std::cout << "Usaste " << obj.getNombre() << "\n";

    if (obj.getTipo() == "curacion") {
        int vidaAntes = vidaAct;
        curar(obj.getValor());
        std::cout << "Te curaste " << vidaAct - vidaAntes << " de vida (" << vidaAct << "/" << vidaMax << ")\n";
    } else if (obj.getTipo() == "ataque") {
        subirAtaque(obj.getValor());
        std::cout << "Tu ataque subio a " << ataque << "\n";
    } else if (obj.getTipo() == "antidoto") {
        quitarEstados();
        std::cout << "Ya no estas envenenado ni quemado\n";
    }

    inventario.erase(inventario.begin() + posicion);
}

bool Jugador::tieneObjetos() const {
    if (inventario.size() > 0) {
        return true;
    }
    return false;
}

void Jugador::ganarExperiencia(int cantidad) {
    experiencia += cantidad;
    std::cout << "Ganaste " << cantidad << " de experiencia (" << experiencia << "/" << expParaSubir << " XP)\n";

    while (experiencia >= expParaSubir) {
        experiencia -= expParaSubir;
        subirNivel();
    }
}

void Jugador::subirNivel() {
    nivel++;
    expParaSubir += 50;
    vidaMax += 10;
    ataque += 2;
    vidaAct = vidaMax;

    std::cout << "\n*** SUBISTE A NIVEL " << nivel << "! ***\n";
    std::cout << "Vida maxima: " << vidaMax << " | Ataque: " << ataque << "\n";
    std::cout << "Recuperas toda tu vida.\n";
}

int Jugador::getNivel() const {
    return nivel;
}

int Jugador::getExperiencia() const {
    return experiencia;
}

int Jugador::getExpParaSubir() const {
    return expParaSubir;
}

void Jugador::guardar(std::ofstream& archivo) const {
    archivo << vidaAct << " " << vidaMax << " " << ataque << "\n";
    archivo << nivel << " " << experiencia << " " << expParaSubir << "\n";
    archivo << turnosQuemado << " " << turnosEnvenenado << "\n";

    archivo << inventario.size() << "\n";
    for (int i = 0; i < inventario.size(); i++) {
        archivo << inventario[i].getNombre() << "\n";
        archivo << inventario[i].getDescripcion() << "\n";
        archivo << inventario[i].getTipo() << "\n";
        archivo << inventario[i].getValor() << "\n";
    }
}

void Jugador::cargar(std::ifstream& archivo) {
    archivo >> vidaAct >> vidaMax >> ataque;
    archivo >> nivel >> experiencia >> expParaSubir;
    archivo >> turnosQuemado >> turnosEnvenenado;

    int cantidad;
    archivo >> cantidad;
    archivo.ignore();

    inventario.clear();
    for (int i = 0; i < cantidad; i++) {
        std::string nombreObj;
        std::string descripcion;
        std::string tipo;
        int valor;

        std::getline(archivo, nombreObj);
        std::getline(archivo, descripcion);
        std::getline(archivo, tipo);
        archivo >> valor;
        archivo.ignore();

        inventario.push_back(Objeto(nombreObj, descripcion, tipo, valor));
    }
}
