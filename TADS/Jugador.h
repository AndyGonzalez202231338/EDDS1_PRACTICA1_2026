#include "Mano.h"
#include "Mazo.h"
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

using namespace std;

class Jugador{
    private: 
        string nombre;
        Mano* mano;
        bool dijoUno;
    public:
        Jugador();
        Jugador(string nombre);
        void robarCarta(Mazo* mazo);
        void tieneCartaJugable(Carta* cartaSuperior);
        void decirUno();
        Carta* jugarCarta(int indice);
        int cartasEnMano();
        string getNombre();
        bool tieneUNO();
};

#endif