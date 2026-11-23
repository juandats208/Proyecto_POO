#ifndef Esfinge_H
#define Esfinge_H
#include <vector>
#include "Entidad.h"

class Esfinge : public Entidad {
private:

    std::vector<std::string> preguntas;
    std::vector<int> respuestas;
    int contadorTurnos;

    bool lanzarAcertijo(Entidad& objetivo);

public:

    //Constructor

    Esfinge();

    //Metodos

    void atacar(Entidad& objetivo) override;
    int getRecompensaExp() const override;

};

#endif
