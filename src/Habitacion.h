#ifndef Habitacion_H
#define Habitacion_H
#include <string>
#include <vector>
#include <map>
#include "Entidad.h"
#include "Objeto.h"
#include "Jugador.h"

class Habitacion {
private:

    std::string nombre;
    std::string descripcion;
    std::string efectoAmbiente;
    std::vector<Entidad*> enemigos;
    std::vector<Objeto> objetos;
    std::map<std::string, Habitacion*> salidas;
    bool salidaBloqueada;

public:

    //Constructor

    Habitacion(const std::string& nombre, const std::string& descripcion, const std::string& efecto);

    //Destructor

    ~Habitacion();

    //Metodos

    void agregarEnemigo(Entidad* e);
    void agregarObjeto(Objeto obj);
    void agregarSalida(const std::string& direccion, Habitacion* h);
    void mostrar() const;
    bool hayEnemigosVivos() const;
    Entidad* getEnemigo() const;
    Habitacion* getSalida(const std::string& direccion) const;
    void desbloquear();
    std::vector<Objeto> entregarObjetos();
    void aplicarEfecto(Jugador* j);

    //Getters

    std::string getNombre() const;
    std::string getEfecto() const;

};

#endif
