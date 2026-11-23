#ifndef MagoRayo_H
#define MagoRayo_H
#include "Jugador.h"

class MagoRayo : public Jugador {
private:

    int probCritico;

public:

    //Constructor

    MagoRayo(const std::string& nombre);

    //Metodos

    void atacar(Entidad& objetivo) override;
    void ataqueFuerte(Entidad& objetivo) override;
    void habilidadEspecial(Entidad& objetivo) override;

};

#endif