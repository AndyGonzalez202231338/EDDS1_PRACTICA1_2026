#include "CartaY.h"
#include "../utils/Colores.h"
#include <iostream>
#include <limits>
using namespace std;

CartaY::CartaY() : Carta(8), colorElegido(-1) {}

CartaY::~CartaY() {}

int CartaY::getTipo() const {
    return 1; // Acción
}

int CartaY::getValor() const {
    return 25;
}

int CartaY::getColor() const {
    return (colorElegido != -1) ? colorElegido : color;
}

void CartaY::setColorElegido(int color) {
    if (color >= 0 && color < 4) {
        colorElegido = color;
    }
}

void CartaY::mostrar() const {
    cout << MAGENTA_BRIL << "Y" << RESET;
}


bool CartaY::esJugable(const Carta& cartaSuperior) const {
    return true;
}

// ejecutarAccion
void CartaY::ejecutarAccion(class JuegoUNO& juego) {
    cout << MAGENTA_BRIL << "\n=== CARTA Y (SALTO + COLOR) ===\n" << RESET;
    
    cout << "Elige un color:\n";
    cout << ROJO << "0: ROJO\n" << RESET;
    cout << AMARILLO << "1: AMARILLO\n" << RESET;
    cout << VERDE << "2: VERDE\n" << RESET;
    cout << AZUL << "3: AZUL\n" << RESET;
    
    int nuevoColor;
    cout << "Opción: ";
    cin >> nuevoColor;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while (cin.fail() || nuevoColor < 0 || nuevoColor > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Color inválido. Elige 0-3: ";
        cin >> nuevoColor;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    setColorElegido(nuevoColor);
    
    cout << "Color cambiado a ";
    switch (nuevoColor) {
        case 0: cout << ROJO << "ROJO" << RESET; break;
        case 1: cout << AMARILLO << "AMARILLO" << RESET; break;
        case 2: cout << VERDE << "VERDE" << RESET; break;
        case 3: cout << AZUL << "AZUL" << RESET; break;
    }
    cout << "\n";
    
    cout << "¡El siguiente jugador pierde su turno!\n";
    juego.siguienteTurno(); // Salta al siguiente jugador
    
    cout << "Presiona Enter para continuar...";
    cin.get();
}

bool CartaY::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 1 && otra.getValor() == 25);
}