#ifndef MAZO_H
#define MAZO_H

#include "NodoCarta.h"

class Mazo {
private:
    NodoCarta* tope;
    int cantidad;

    void generarCartasClasicas();
    void generarCartasFlip();

public:
    Mazo();
    ~Mazo();
    
    void inicializarClasico();
    void inicializarFlip();
    void barajar();
    void apilar(Carta* carta);
    Carta* desapilar();
    void imprimirMazo() const;

    void inicializarClasico(int numJugadores);
    void inicializarFlip(int numJugadores);
    void agregarMazoCompleto();
    void agregarMazoFlipCompleto();
    bool estaVacio() const;
    int size() const;
    void vaciar();
};

#endif