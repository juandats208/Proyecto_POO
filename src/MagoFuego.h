#ifndef MagoFuego_H
#define MagoFuego_H
#include "Jugador.h"

class MagoFuego : public Jugador {
private:

    int turnosQuemadura;

public:

    //Constructor

    MagoFuego(const std::string& nombre);

    //Metodos

    void atacar(Entidad& objetivo) override;
    void ataqueFuerte(Entidad& objetivo) override;
    void habilidadEspecial(Entidad& objetivo) override;

};

#endif
