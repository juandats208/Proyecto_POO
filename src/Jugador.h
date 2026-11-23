#ifndef Jugador_H
#define Jugador_H
#include <string>
#include <vector>
#include "Entidad.h"
#include "Objeto.h"

class Jugador : public Entidad {
protected:

    std::vector<Objeto> inventario;
    int recargaEspecial;

public:

    //Constructor

    Jugador(const std::string& nombre, int vida, int ataque);

    //Metodos

    void atacar(Entidad& objetivo) override;
    virtual void ataqueFuerte(Entidad& objetivo);
    virtual void habilidadEspecial(Entidad& objetivo);
    bool puedeUsarEspecial() const;
    int getRecargaEspecial() const;
    void reducirRecarga();
    void agregarObjeto(Objeto obj);
    void mostrarInventario() const;
    void usarObjeto(int indice);
    bool tieneObjetos() const;

};

#endif
