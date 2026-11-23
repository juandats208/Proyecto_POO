#ifndef Jugador_H
#define Jugador_H
#include <string>
#include <vector>
#include <fstream>
#include "Entidad.h"
#include "Objeto.h"

class Jugador : public Entidad {
protected:

    std::vector<Objeto> inventario;
    int debilesSeguidos;   // -> ataques debiles desde el ultimo fuerte
    bool usoDebil;         // -> uso un ataque debil desde la ultima especial
    bool usoFuerte;        // -> uso un ataque fuerte desde la ultima especial
    int nivel;
    int experiencia;
    int expParaSubir;

private:

    void subirNivel();


public:

    //Constructor

    Jugador(const std::string& nombre, int vida, int ataque);

    //Ataques

    virtual bool resisteCalor() const { return false; }
    void atacar(Entidad& objetivo) override;
    virtual void ataqueFuerte(Entidad& objetivo);
    virtual void habilidadEspecial(Entidad& objetivo);

    //Lo que se llama desde el combate

    void usarAtaqueDebil(Entidad& objetivo);
    void usarAtaqueFuerte(Entidad& objetivo);
    void usarHabilidadEspecial(Entidad& objetivo);
    bool puedeUsarFuerte() const;
    bool puedeUsarEspecial() const;
    void mostrarProgresoFuerte() const;
    void mostrarProgresoEspecial() const;

    //Experiencia y niveles

    void ganarExperiencia(int cantidad);
    int getNivel() const;
    int getExperiencia() const;
    int getExpParaSubir() const;

    //Guardar y cargar partida

    void guardar(std::ofstream& archivo) const;
    void cargar(std::ifstream& archivo);

    //Inventario

    void agregarObjeto(Objeto obj);
    void mostrarInventario() const;
    void usarObjeto(int indice);
    bool tieneObjetos() const;

};

#endif