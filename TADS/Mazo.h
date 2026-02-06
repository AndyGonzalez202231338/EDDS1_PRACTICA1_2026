#ifndef MAZO_H
#define MAZO_H

#include "NodoCarta.h"
class Mazo {
    private:
        NodoCarta* final;
        int tamanio;
    public:
        Mazo();
        void inicializar(int numJugadores);
        void barajar();
        void apilarCarta(Carta* carta);
        Carta* sacarCarta();
        bool estaVacio(); 
        int getTamanio();
};
#endif