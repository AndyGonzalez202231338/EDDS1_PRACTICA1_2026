#ifndef MAZO_H
#define MAZO_H

#include "NodoCarta.h"

struct Cara {
    int color;
    int tipo;
    int valor;
};

class Mazo {
private:
    NodoCarta* tope;
    int cantidad;

    void generarCarasClaras(Cara* caras, int& total);
    void generarCarasOscuras(Cara* caras, int& total);
    void barajarCaras(Cara* caras, int n);

public:
    Mazo();

    void inicializarClasico(int numJugadores);
    void inicializarFlip(int numJugadores);
    void barajar();
    void apilar(const Carta& carta);
    Carta desapilar();

    void imprimirMazo() const;           

    
    bool estaVacio() const;
    int size() const;
};

#endif
