#ifndef Objeto_H
#define Objeto_H
#include <string>

class Objeto {
private:

    std::string nombre;
    std::string descripcion;
    std::string tipo;
    int valor;

public:

    //Constructor

    Objeto(const std::string& nombre, const std::string& descripcion, const std::string& tipo, int valor);

    //Metodos

    void mostrar() const;

    //Getters

    std::string getNombre() const;
    std::string getDescripcion() const;
    std::string getTipo() const;
    int getValor() const;

};

#endif