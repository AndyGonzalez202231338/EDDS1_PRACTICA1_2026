#ifndef MANO_H
#define MANO_H

#include "NodoCarta.h"

class Mano {
    private:
        NodoCarta* cabeza;
        int tamanio;
    public:
        Mano();
        void agregarCarta(Carta* carta);
        Carta* eliminarCarta(int indice);
        Carta* obtenerCarta(int indice);
        bool tieneCartaJugable(Carta* cartaSuperior);
        int contarCartas();
};

#endif