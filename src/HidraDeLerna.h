#ifndef HidraDeLerna_H
#define HidraDeLerna_H
#include "Entidad.h"

class HidraDeLerna : public Entidad {
private:

    int cabezas;
    int maxCabezas;
    int cabezasPorCrecer;

public:

    //Constructor

    HidraDeLerna();

    //Metodos

    void atacar(Entidad& objetivo) override;
    void recibirDanio(int cantidad, std::string tipo) override;
    void regenerar();

    //Getters

    int getCabezas() const;

};

#endif
