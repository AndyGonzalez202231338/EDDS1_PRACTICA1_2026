#include "CartaAccion.h"
#include "JuegoUNO.h"
#include <iostream>
using namespace std;

CartaAccion::CartaAccion(int color, int tipoAccion) 
    : Carta(color), tipoAccion(tipoAccion) {}

CartaAccion::~CartaAccion() {}

int CartaAccion::getTipo() const {
    return 1;
}

int CartaAccion::getValor() const {
    return tipoAccion;
}

void CartaAccion::mostrar() const {
    switch (color) {
        case 0: cout << "ROJO "; break;
        case 1: cout << "AMARILLO "; break;
        case 2: cout << "VERDE "; break;
        case 3: cout << "AZUL "; break;
    }
    
    switch (tipoAccion) {
        case 10: cout << "SALTAR"; break;
        case 11: cout << "REVERTIR"; break;
        case 12: cout << "+2"; break;
    }
}

void CartaAccion::ejecutarAccion(class JuegoUNO& juego) {
    switch (tipoAccion) {
        case 10: // SKIP
            cout << "-> ¡SALTAR! El siguiente jugador pierde su turno.\n";
            juego.siguienteTurno(); // Salta un jugador
            break;
            
        case 11: // REVERSE
            juego.invertirSentido();
            if (juego.getNumJugadores() == 2) {
                // Con 2 jugadores, reverse funciona como skip
                juego.siguienteTurno();
            }
            break;
            
        case 12: // +2
            cout << "+2 El siguiente jugador roba 2 cartas.\n";
            juego.siguienteTurno();
            for (int i = 0; i < 2; i++) {
                juego.robarCartaJugadorActual();
            }
            break;
    }
}

bool CartaAccion::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 1 && otra.getValor() == tipoAccion);
}