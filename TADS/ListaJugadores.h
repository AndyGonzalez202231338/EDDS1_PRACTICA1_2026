#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H
#include "NodoJugador.h"

class ListaJugadores {
    private: 
        NodoJugador* cabeza;
        int tamanio;
        bool sentidoHorario;
    public:
        ListaJugadores();
        void agregarJugador(Jugador* jugador);
        Jugador* obtenerJugadorActual();
        void invertirSentido();
        int getTamanio();
};

#endif