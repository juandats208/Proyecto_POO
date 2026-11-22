#ifndef MagoHielo_H
#define MagoHielo_H
#include "Jugador.h"

class MagoHielo : public Jugador {
public:

    //Constructor

    MagoHielo(const std::string& nombre);

    //Metodos

    void atacar(Entidad& objetivo) const override;
    void ataqueFuerte(Entidad& objetivo) override;
    void habilidadEspecial(Entidad& objetivo) override;

};

#endif
