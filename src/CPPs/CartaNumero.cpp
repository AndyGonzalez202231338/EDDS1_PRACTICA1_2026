#include "CartaNumero.h"
#include <iostream>
using namespace std;

CartaNumero::CartaNumero(int color, int numero) 
    : Carta(color), numero(numero) {}

CartaNumero::~CartaNumero() {}

int CartaNumero::getTipo() const {
    return 0;
}

int CartaNumero::getValor() const {
    return numero;
}

void CartaNumero::mostrar() const {
    switch (color) {
        case 0: cout << "ROJO "; break;
        case 1: cout << "AMARILLO "; break;
        case 2: cout << "VERDE "; break;
        case 3: cout << "AZUL "; break;
    }
    cout << numero;
}

void CartaNumero::ejecutarAccion(class JuegoUNO& juego) {
    // Las cartas numéricas no tienen acción especial
    cout << "Carta numérica sin efecto especial.\n";
}

bool CartaNumero::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 0 && otra.getValor() == numero);
}