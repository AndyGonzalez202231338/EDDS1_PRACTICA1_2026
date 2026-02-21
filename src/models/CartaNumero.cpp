#include "CartaNumero.h"
#include <iostream>
using namespace std;
#include <limits>

#define RESET   "\033[0m"
#define BG_MAGENTA  "\033[45m"

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
    cout << BG_MAGENTA << "Carta numérica sin efecto especial, avanza turno." << RESET << "\n";
}

bool CartaNumero::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 0 && otra.getValor() == numero);
}