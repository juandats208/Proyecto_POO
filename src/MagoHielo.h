#ifndef MagoHielo_H
#define MagoHielo_H
#include "Jugador.h"

class MagoHielo : public Jugador {
public:

    //Constructor

    MagoHielo(const std::string& nombre);

    //Metodos
    bool resisteCalor() const override { return true; }
    void atacar(Entidad& objetivo) override;
    void ataqueFuerte(Entidad& objetivo) override;
    void habilidadEspecial(Entidad& objetivo) override;

};

#endif