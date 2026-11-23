#ifndef Jugador_H
#define Jugador_H
#include <string>
#include <vector>
#include "Entidad.h"
#include "Objeto.h"

class Jugador : public Entidad {
protected:

    std::vector<Objeto> inventario;
    int debilesSeguidos;   // ataques debiles desde el ultimo fuerte
    bool usoDebil;         // uso un ataque debil desde la ultima especial
    bool usoFuerte;        // uso un ataque fuerte desde la ultima especial

public:

    //Constructor

    Jugador(const std::string& nombre, int vida, int ataque);

    //Ataques (cada mago los sobrescribe)

    void atacar(Entidad& objetivo) override;
    virtual void ataqueFuerte(Entidad& objetivo);
    virtual void habilidadEspecial(Entidad& objetivo);

    //Lo que se llama desde el combate (lleva la cuenta de los combos)

    void usarAtaqueDebil(Entidad& objetivo);
    void usarAtaqueFuerte(Entidad& objetivo);
    void usarHabilidadEspecial(Entidad& objetivo);
    bool puedeUsarFuerte() const;
    bool puedeUsarEspecial() const;
    void mostrarProgresoFuerte() const;
    void mostrarProgresoEspecial() const;

    //Inventario

    void agregarObjeto(Objeto obj);
    void mostrarInventario() const;
    void usarObjeto(int indice);
    bool tieneObjetos() const;

};

#endif
