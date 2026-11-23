#ifndef Entidad_H
#define Entidad_H
#include <string>

class Entidad {
protected:

    std::string nombre;
    int vidaAct;
    int vidaMax;
    int ataque;
    int turnosEnvenenado;
    int turnosQuemado;
    bool congelado;

public:

    //Metodos

    virtual void atacar(Entidad& objetivo) = 0;
    virtual void recibirDanio(int cantidad, std::string tipo);
    void curar(int cantidad);
    bool estaVivo() const;
    void congelar();
    void quemar(int turnos);
    void envenenar(int turnos);
    void quitarEstados();
    bool procesarEstados();
    void subirAtaque(int cantidad);
    virtual int getRecompensaExp() const;


    //Constructor

    Entidad(const std::string& nombre, int vida, int ataque);

    //Destructor

    virtual ~Entidad();

    //Getters

    std::string getNombre() const;
    int getVidaAct() const;
    int getVidaMax() const;
    int getAtaque() const;

};

#endif
