#include "CartaComodin.h"
#include "JuegoUNO.h"
#include <iostream>
using namespace std;

#define RESET   "\033[0m"

#define NEGRO   "\033[30m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BLANCO  "\033[37m"

#define GRIS_OSCURO     "\033[90m"
#define ROJO_BRILLANTE  "\033[91m"
#define VERDE_BRILLANTE "\033[92m"
#define AMAR_BRILLANTE  "\033[93m"
#define AZUL_BRILLANTE  "\033[94m"
#define MAGENTA_BRIL    "\033[95m"
#define CYAN_BRILLANTE  "\033[96m"
#define BLANCO_BRIL     "\033[97m"

#define BG_ROJO     "\033[41m"
#define BG_VERDE    "\033[42m"
#define BG_AMARILLO "\033[43m"
#define BG_AZUL     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_BLANCO   "\033[47m"

CartaComodin::CartaComodin(int tipoComodin, bool esOscuro) 
    : Carta(4), tipoComodin(tipoComodin), colorElegido(-1) {
    ladoOscuro = esOscuro;
}

CartaComodin::~CartaComodin() {}

int CartaComodin::getTipo() const {
    return 2;
}

int CartaComodin::getValor() const {
    return tipoComodin;
}

int CartaComodin::getColor() const {
    // Si ya se eligió un color, devolver ese; si no, devolver negro (4)
    return (colorElegido != -1) ? colorElegido : color;
}

void CartaComodin::setColorElegido(int color) {
    if (color >= 0 && color < 4) {
        colorElegido = color;
    }
}

void CartaComodin::mostrar() const {
    if (!ladoOscuro) {
        if (colorElegido != -1) {
            // Mostrar con el color elegido
            switch (colorElegido) {
                case 0: cout << "ROJO "; break;
                case 1: cout << "AMARILLO "; break;
                case 2: cout << "VERDE "; break;
                case 3: cout << "AZUL "; break;
            }
            switch (tipoComodin) {
                case 13: cout << "+4"; break;
                case 14: cout << "CAMBIO COLOR"; break;
            }
        } else {
            cout << "NEGRO ";
            switch (tipoComodin) {
                case 13: cout << "+4"; break;
                case 14: cout << "CAMBIO COLOR"; break;
            }
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
                // Elegir color
                cout << "@ Elige un color:\n";
                cout << "0: ROJO"<<endl;
                cout << "1: AMARILLO"<<endl;
                cout << "2: VERDE"<<endl;
                cout << "3: AZUL"<<endl;
                int nuevoColor;
                cin >> nuevoColor;
                setColorElegido(nuevoColor);
                
                juego.siguienteTurno();
                for (int i = 0; i < 4; i++) {
                    juego.robarCartaJugadorActual();
                }
                break;
                
            case 14: // CAMBIO COLOR
                cout <<BG_MAGENTA<<BLANCO<< "@" <<BG_ROJO<< " ¡CAM"<<BG_AMARILLO<<"BIO D"<<BG_VERDE"E COL"<<BG_AZUL<<"OR! "<<RESET<<"   Elige nuevo color:\n";
                cout <<ROJO<< "0: ROJO"<<RESET<<endl;
                cout <<AMARILLO<< "1: AMARILLO"<<RESET<<endl;
                cout <<VERDE<< "2: VERDE"<<RESET<<endl;
                cout <<AZUL<< "3: AZUL"<<RESET<<endl;
                int nuevoColor2;
                cin >> nuevoColor2;
                setColorElegido(nuevoColor2);
                break;
        }
    } else {
        // Versiones oscuras (mantener igual)
        switch (tipoComodin) {
            case 23: // WILD DARK
                cout << "<> WILD DARK: Elige color y voltea todas las cartas.\n";
                int nuevoColor3;
                cin >> nuevoColor3;
                setColorElegido(nuevoColor3);
                // Lógica para voltear todas las cartas
                break;
                
            case 24: // WILD +6
                cout << "<> WILD +6: Elige color y el siguiente roba 6.\n";
                int nuevoColor4;
                cin >> nuevoColor4;
                setColorElegido(nuevoColor4);
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