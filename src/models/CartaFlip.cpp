#include "CartaFlip.h"
#include "JuegoUNO.h"
#include <iostream>
using namespace std;

CartaFlip::CartaFlip(int cClaro, int tClaro, int vClaro, 
                     int cOscuro, int tOscuro, int vOscuro)
    : Carta(cClaro), 
      colorClaro(cClaro), tipoClaro(tClaro), valorClaro(vClaro),
      colorOscuro(cOscuro), tipoOscuro(tOscuro), valorOscuro(vOscuro),
      ladoOscuro(false) {}

CartaFlip::~CartaFlip() {}

int CartaFlip::getColor() const {
    return ladoOscuro ? colorOscuro : colorClaro;
}

int CartaFlip::getTipo() const {
    return ladoOscuro ? tipoOscuro : tipoClaro;
}

int CartaFlip::getValor() const {
    return ladoOscuro ? valorOscuro : valorClaro;
}

void CartaFlip::mostrar() const {
    if (ladoOscuro) {
        switch (colorOscuro) {
            case 0: cout << "ROJO OSCURO "; break;
            case 1: cout << "AMARILLO OSCURO "; break;
            case 2: cout << "VERDE OSCURO "; break;
            case 3: cout << "AZUL OSCURO "; break;
            case 4: cout << "NEGRO OSCURO "; break;
        }
        
        if (tipoOscuro == 1) {
            switch (valorOscuro) {
                case 20: cout << "SALTAR TODOS"; break;
                case 21: cout << "REVERTIR"; break;
                case 22: cout << "+6"; break;
            }
        } else if (tipoOscuro == 2) {
            switch (valorOscuro) {
                case 23: cout << "WILD DARK"; break;
                case 24: cout << "WILD +6"; break;
            }
        } else if (tipoOscuro == 0) {
            cout << valorOscuro;
        }
    } else {
        switch (colorClaro) {
            case 0: cout << "ROJO "; break;
            case 1: cout << "AMARILLO "; break;
            case 2: cout << "VERDE "; break;
            case 3: cout << "AZUL "; break;
        }
        
        if (tipoClaro == 1) {
            switch (valorClaro) {
                case 10: cout << "SALTAR"; break;
                case 11: cout << "REVERTIR"; break;
                case 12: cout << "+2"; break;
            }
        } else if (tipoClaro == 2) {
            switch (valorClaro) {
                case 13: cout << "+4"; break;
                case 14: cout << "CAMBIO COLOR"; break;
            }
        } else if (tipoClaro == 0) {
            cout << valorClaro;
        }
    }
}

void CartaFlip::voltear() {
    ladoOscuro = !ladoOscuro;
}

bool CartaFlip::esLadoOscuro() const {
    return ladoOscuro;
}

bool CartaFlip::mismoTipoYValor(const Carta& otra) const {
    // Compara según el lado actual
    if (getTipo() == otra.getTipo() && getValor() == otra.getValor()) {
        return true;
    }
    return false;
}

void CartaFlip::ejecutarAccion(class JuegoUNO& juego) {
    if (ladoOscuro) {
        // ========================= Logica para lado oscuro =========================
        if (tipoOscuro == 1) {
            switch (valorOscuro) {
                case 20: // SKIP ALL
                    cout << "->  ¡SALTAR TODOS! Todos pierden un turno.\n";
                    // Lógica especial para saltar todos
                    break;
                case 21: // REVERSE (igual que claro)
                    juego.invertirSentido();
                    break;
                case 22: // +6
                    cout << "+6 El siguiente jugador roba 6 cartas.\n";
                    juego.siguienteTurno();
                    for (int i = 0; i < 6; i++) {
                        juego.robarCartaJugadorActual();
                    }
                    break;
            }
        } else if (tipoOscuro == 2) {
            switch (valorOscuro) {
                case 23: // WILD DARK
                    cout << "<> WILD DARK: Elige color y voltea todas las cartas.\n";
                    break;
                case 24: // WILD +6
                    cout << "<> WILD +6: Elige color y el siguiente roba 6.\n";
                    juego.siguienteTurno();
                    for (int i = 0; i < 6; i++) {
                        juego.robarCartaJugadorActual();
                    }
                    break;
            }
        }
    } else {
        if (tipoClaro == 1) {
            switch (valorClaro) {
                case 10: // SKIP
                    cout << "->  ¡SALTAR! El siguiente pierde turno.\n";
                    juego.siguienteTurno();
                    break;
                case 11: // REVERSE
                    juego.invertirSentido();
                    if (juego.getNumJugadores() == 2) {
                        juego.siguienteTurno();
                    }
                    break;
                case 12: // +2
                    cout << "+2 El siguiente roba 2 cartas.\n";
                    juego.siguienteTurno();
                    for (int i = 0; i < 2; i++) {
                        juego.robarCartaJugadorActual();
                    }
                    break;
            }
        } else if (tipoClaro == 2) {
            switch (valorClaro) {
                case 13: // +4
                    cout << "+4 El siguiente roba 4 cartas.\n";
                    juego.siguienteTurno();
                    for (int i = 0; i < 4; i++) {
                        juego.robarCartaJugadorActual();
                    }
                    break;
                case 14: // CAMBIO COLOR
                    cout << "@ CAMBIO COLOR: Elige nuevo color.\n";
                    // Lógica para elegir color
                    break;
            }
        }
    }
}

bool CartaFlip::esJugable(const Carta& cartaSuperior) const {
    if (getColor() == cartaSuperior.getColor()) return true;
    if (getTipo() == cartaSuperior.getTipo() && 
        getValor() == cartaSuperior.getValor()) return true;
    if (getTipo() == 2) return true; // Comodines
    return false;
}