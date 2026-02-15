#include "CartaComodin.h"
#include "JuegoUNO.h"
#include <iostream>
using namespace std;

CartaComodin::CartaComodin(int tipoComodin, bool esOscuro) 
    : Carta(4), tipoComodin(tipoComodin) {
    ladoOscuro = esOscuro;
}

CartaComodin::~CartaComodin() {}

int CartaComodin::getTipo() const {
    return 2;
}

int CartaComodin::getValor() const {
    return tipoComodin;
}

void CartaComodin::mostrar() const {
    if (!ladoOscuro) {
        cout << "NEGRO ";
        switch (tipoComodin) {
            case 13: cout << "+4"; break;
            case 14: cout << "CAMBIO COLOR"; break;
        }
    } else {
        cout << "NEGRO OSCURO ";
        switch (tipoComodin) {
            case 23: cout << "WILD DARK"; break;
            case 24: cout << "WILD +6"; break;
        }
    }
}

bool CartaComodin::esJugable(const Carta& cartaSuperior) const {
    // Los comodines siempre son jugables
    return true;
}

void CartaComodin::ejecutarAccion(class JuegoUNO& juego) {
    if (!ladoOscuro) {
        switch (tipoComodin) {
            case 13: // +4
                cout << "+4 El siguiente jugador roba 4 cartas.\n";
                juego.siguienteTurno();
                for (int i = 0; i < 4; i++) {
                    juego.robarCartaJugadorActual();
                }
                break;
                
            case 14: // CAMBIO COLOR
                cout << "@ ¡CAMBIO DE COLOR! Elige nuevo color:\n";
                cout << "0: ROJO, 1: AMARILLO, 2: VERDE, 3: AZUL\n";
                int nuevoColor;
                cin >> nuevoColor;
                // Aquí deberías implementar el cambio de color
                break;
        }
    } else {
        // Versiones oscuras
        switch (tipoComodin) {
            case 23: // WILD DARK
                cout << "<>WILD DARK: Elige color y voltea todas las cartas.\n";
                // Lógica especial para voltear todas las cartas
                break;
                
            case 24: // WILD +6
                cout << "<>WILD +6: El siguiente jugador roba 6 cartas.\n";
                juego.siguienteTurno();
                for (int i = 0; i < 6; i++) {
                    juego.robarCartaJugadorActual();
                }
                break;
        }
    }
}

bool CartaComodin::mismoTipoYValor(const Carta& otra) const {
    return false; // Los comodines no coinciden por valor
}

bool CartaComodin::esComodin() const {
    return true;
}