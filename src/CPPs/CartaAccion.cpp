#include "CartaAccion.h"
#include "JuegoUNO.h"
#include <iostream>
using namespace std;

#define RESET   "\033[0m"

#define BG_ROJO     "\033[41m"
#define BG_VERDE    "\033[42m"
#define BG_AMARILLO "\033[43m"
#define BG_AZUL     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_BLANCO   "\033[47m"

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
            cout <<BG_MAGENTA <<"-> ¡SALTAR! El siguiente jugador pierde su turno."<<RESET<<"\n";
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
            cout <<BG_MAGENTA<< "+2 El siguiente jugador roba 2 cartas."<<RESET<<"\n";
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