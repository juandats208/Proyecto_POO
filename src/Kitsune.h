#ifndef Kitsune_H
#define Kitsune_H
#include "Entidad.h"

class Kitsune : public Entidad {
private:

    int probEsquivar;

public:

    //Constructor

    Kitsune();

    //Metodos

    void atacar(Entidad& objetivo) override;
    void recibirDanio(int cantidad, std::string tipo) override;

};

#endif
