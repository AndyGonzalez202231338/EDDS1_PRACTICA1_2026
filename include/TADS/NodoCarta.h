#ifndef NODOCARTA_H
#define NODOCARTA_H

#include "Carta.h"

class NodoCarta {
public:
    Carta* dato;
    NodoCarta* siguiente;

    NodoCarta(Carta* carta);
};

#endif
