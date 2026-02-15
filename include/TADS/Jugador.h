#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Mano.h"
#include "Mazo.h"

using namespace std;

class Jugador {
private:
    string nombre;
    Mano mano;
    bool dijoUNO;

public:
    Jugador();
    Jugador(string nombre);
    ~Jugador(); 

    void robarCarta(Mazo& mazo);
    Carta* jugarCarta(int indice);

    int cartasEnMano() const;
    void mostrarMano() const;
    bool tieneUnaCarta() const;
    bool haDichoUNO() const;

    void cantarUNO();
    void resetearUNO();

    string getNombre() const;
    Mano& getMano();
    const Mano& getMano() const;
};

#endif