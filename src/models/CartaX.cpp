#include "CartaX.h"
#include "../utils/Colores.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

CartaX::CartaX() : Carta(8), colorElegido(-1) {
    srand(time(nullptr));
}

CartaX::~CartaX() {}

int CartaX::getTipo() const {
    return 2;
}

int CartaX::getValor() const {
    return 15; // Valor para carta X
}

int CartaX::getColor() const {
    return (colorElegido != -1) ? colorElegido : 8;
}


void CartaX::mostrar() const {
    cout << BLANCO_BRIL << "X" << RESET;
}

bool CartaX::esJugable(const Carta& cartaSuperior) const {
    return true;
}

void CartaX::ejecutarAccion(class JuegoUNO& juego) {
    cout << MAGENTA_BRIL << "\n=== CARTA X (COMODÍN ALEATORIO) ===\n" << RESET;
    
    int nuevoColor = rand() % 4;
    colorElegido = nuevoColor;
    
    cout << "El sistema eligió el color: ";
    switch (nuevoColor) {
        case 0: cout << ROJO << "ROJO" << RESET; break;
        case 1: cout << AMARILLO << "AMARILLO" << RESET; break;
        case 2: cout << VERDE << "VERDE" << RESET; break;
        case 3: cout << AZUL << "AZUL" << RESET; break;
    }
    cout << "\n";
    
    cout << "Presiona Enter para continuar...";
    cin.get();
}


bool CartaX::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 2 && otra.getValor() == 15);
}