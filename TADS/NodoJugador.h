#ifndef NODOJUGADOR_H
#define NODOJUGADOR_H

#include "Jugador.h"

class NodoJugador {
public: 
    Jugador* jugador;
    NodoJugador* siguiente;
    NodoJugador(Jugador* jugador);
};
#endif