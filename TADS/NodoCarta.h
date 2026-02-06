#include "Carta.h"

#ifndef NODOCARTA_H
#define NODOCARTA_H

class NodoCarta {
    private: 
        Carta* dato;
        NodoCarta* siguiente;
    public:
        NodoCarta(Carta* dato);
};

#endif



