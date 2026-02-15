#ifndef CARTA_H
#define CARTA_H

#include <iostream>
using namespace std;

// Clase base abstracta
class Carta {
protected:
    int color;
    bool ladoOscuro;

public:
    Carta(int color);
    virtual ~Carta();

    virtual int getColor() const;
    virtual int getTipo() const = 0;
    virtual int getValor() const = 0;
    virtual void mostrar() const = 0;
    
    virtual bool esJugable(const Carta& cartaSuperior) const;
    virtual void ejecutarAccion(class JuegoUNO& juego) = 0;
    
    virtual void voltear();
    virtual bool esLadoOscuro() const;

protected:
    virtual bool mismoTipoYValor(const Carta& otra) const = 0;
    virtual bool esComodin() const;
};

#endif