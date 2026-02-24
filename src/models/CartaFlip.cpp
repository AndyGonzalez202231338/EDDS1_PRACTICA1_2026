#include "CartaFlip.h"
#include "JuegoUNO.h"
#include "CartaNumero.h"
#include "CartaAccion.h"
#include "CartaComodin.h"
#include "../utils/Colores.h"
#include <limits>
#include <iostream>
using namespace std;

JuegoUNO* CartaFlip::juegoActual = nullptr;

CartaFlip::CartaFlip(int cClaro, int tClaro, int vClaro, int cOscuro, int tOscuro, int vOscuro)
    : Carta(cClaro), 
      colorClaro(cClaro), tipoClaro(tClaro), valorClaro(vClaro),
      colorOscuro(cOscuro), tipoOscuro(tOscuro), valorOscuro(vOscuro),
      ladoOscuro(false) {}

CartaFlip::~CartaFlip() {}

int CartaFlip::getColor() const {
    if (juegoActual == nullptr) {
        return ladoOscuro ? colorOscuro : colorClaro;
    }
    
    bool modoOscuro = juegoActual->isModoOscuroActivo();
    
    if (modoOscuro) {
        // MODO OSCURO: TODAS las cartas deben mostrar color oscuro
        if (tipoClaro == 2 || tipoOscuro == 2) { // Es comodín
            if (color != colorClaro && color != colorOscuro) {
                // Ya tiene un color elegido, mantenerlo
                return color;
            }
            // Comodín sin color elegido, usar el color oscuro por defecto
            return 8;
        }
        
        // No es comodín, forzar color oscuro
        if (ladoOscuro) {
            return colorOscuro; 
        } else {
            switch (colorClaro) {
                case 0: return 4; // Rojo = Rosa
                case 1: return 5; // Amarillo = Violeta
                case 2: return 6; // Verde = Naranja
                case 3: return 7; // Azul = Turquesa
                default: return colorClaro;
            }
        }
    } else {
        if (tipoClaro == 2 || tipoOscuro == 2) { 
            if (color != colorClaro && color != colorOscuro && color < 4) {
                return color;
            }
            // Comodín sin color elegido, usar blanco
            return 8;
        }
        
        if (!ladoOscuro) {
            return colorClaro;
        } else {
            
            switch (colorOscuro) {
                case 4: return 0; // Rosa = Rojo
                case 5: return 1; // Violeta = Amarillo
                case 6: return 2; // Naranja = Verde
                case 7: return 3; // Turquesa = Azul
                default: return colorOscuro;
            }
        }
    }
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
            case 4: cout << "ROSA "; break;      // Rojo oscuro = Rosa
            case 5: cout << "VIOLETA "; break;   // Amarillo oscuro = Violeta
            case 6: cout << "NARANJA "; break;   // Verde oscuro = Naranja
            case 7: cout << "TURQUESA "; break;  // Azul oscuro = Turquesa
            case 8: cout << "BLANCO "; break;    // Comodín oscuro
            default: cout << "DESCONOCIDO "; break;
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
                case 20: { // SKIP ALL
                    cout << MAGENTA_BRIL << "¡SALTAR TODOS! Todos pierden un turno.\n" << RESET;
                    juego.siguienteTurno();
                    break;
                }
                case 21: // REVERSE
                    juego.invertirSentido();
                    if (juego.getNumJugadores() == 2) {
                        juego.siguienteTurno();
                    }
                    break;
                case 22: { // +6
                    cout << MAGENTA_BRIL << "+6 El siguiente jugador roba 6 cartas.\n" << RESET;
                    juego.siguienteTurno();
                    Jugador& siguiente = juego.obtenerJugadorActual();
                    for (int i = 0; i < 6; i++) {
                        juego.robarCartaCastigo(siguiente);
                    }
                    break;
                }
            }
                } else if (tipoOscuro == 2) {
            switch (valorOscuro) {
                case 23: { // WILD DARK
                    cout << MAGENTA_BRIL << "\n=== WILD DARK ===\n" << RESET;
                    cout << "Elige un color:\n";
                    cout << MAGENTA_BRIL << "4: ROSA\n" << RESET;
                    cout << MAGENTA << "5: VIOLETA\n" << RESET;
                    cout << AMAR_BRILLANTE << "6: NARANJA\n" << RESET;
                    cout << CYAN_BRILLANTE << "7: TURQUESA\n" << RESET;
                    
                    int nuevoColor;
                    cout << "Opción: ";
                    cin >> nuevoColor;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    while (cin.fail() || nuevoColor < 4 || nuevoColor > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Color inválido. Elige 4-7: ";
                        cin >> nuevoColor;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    
                    // Guardar color en la carta
                    color = nuevoColor;
                    
                    cout << "Color cambiado a ";
                    switch (nuevoColor) {
                        case 4: cout << MAGENTA_BRIL << "ROSA" << RESET; break;
                        case 5: cout << MAGENTA << "VIOLETA" << RESET; break;
                        case 6: cout << AMAR_BRILLANTE << "NARANJA" << RESET; break;
                        case 7: cout << CYAN_BRILLANTE << "TURQUESA" << RESET; break;
                    }
                    cout << "\n";
                    
                    cout << "Presiona Enter para voltear todas las cartas...";
                    cin.get();
                    
                    juego.cambiarModo();
                    break;
                }
                case 24: { // WILD +6
                    cout << MAGENTA_BRIL << "\n=== WILD +6 ===\n" << RESET;
                    cout << "Elige un color:\n";
                    cout << MAGENTA_BRIL << "4: ROSA\n" << RESET;
                    cout << MAGENTA << "5: VIOLETA\n" << RESET;
                    cout << AMAR_BRILLANTE << "6: NARANJA\n" << RESET;
                    cout << CYAN_BRILLANTE << "7: TURQUESA\n" << RESET;
                    
                    int nuevoColor;
                    cout << "Opción: ";
                    cin >> nuevoColor;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    while (cin.fail() || nuevoColor < 4 || nuevoColor > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Color inválido. Elige 4-7: ";
                        cin >> nuevoColor;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    
                    color = nuevoColor;
                    
                    cout << "Color cambiado a ";
                    switch (nuevoColor) {
                        case 4: cout << MAGENTA_BRIL << "ROSA" << RESET; break;
                        case 5: cout << MAGENTA << "VIOLETA" << RESET; break;
                        case 6: cout << AMAR_BRILLANTE << "NARANJA" << RESET; break;
                        case 7: cout << CYAN_BRILLANTE << "TURQUESA" << RESET; break;
                    }
                    cout << "\n";
                    
                    juego.siguienteTurno();
                    Jugador& siguiente = juego.obtenerJugadorActual();
                    for (int i = 0; i < 6; i++) {
                        juego.robarCartaCastigo(siguiente);
                    }
                    break;
                }
            }
        }
    } else {
        // Lado claro
        if (tipoClaro == 1) { // Acción
            CartaAccion* temp = new CartaAccion(colorClaro, valorClaro);
            temp->ejecutarAccion(juego);
            delete temp;
            
        } else if (tipoClaro == 2) { // Comodín
            CartaComodin* temp = new CartaComodin(valorClaro, false);
            
            temp->ejecutarAccion(juego);
            
            int colorElegido = temp->getColor();
            if (colorElegido >= 0 && colorElegido < 4) {
                color = colorElegido;  
            }
            
            delete temp;
        }
    }
}

bool CartaFlip::esJugable(const Carta& cartaSuperior) const {
    if (cartaSuperior.getTipo() == 3) {
        return true;
    }
    
    if (getColor() == cartaSuperior.getColor()) return true;
    
    if (getTipo() == cartaSuperior.getTipo() && 
        getValor() == cartaSuperior.getValor()) return true;
    
    if (getTipo() == 2) return true;
    
    return false;
}