#include "Carta.h"

Carta::Carta() {
    ladoOscuro = false;
}

Carta::Carta(int cClaro, int tClaro, int vClaro, int cOscuro, int tOscuro, int vOscuro) {
    colorClaro = cClaro;
    tipoClaro = tClaro;
    valorClaro = vClaro;

    colorOscuro = cOscuro;
    tipoOscuro = tOscuro;
    valorOscuro = vOscuro;

    ladoOscuro = false;
}

void Carta::voltear() {
    ladoOscuro = !ladoOscuro;
}

int Carta::getColor() const {
    return ladoOscuro ? colorOscuro : colorClaro;
}

int Carta::getTipo() const {
    return ladoOscuro ? tipoOscuro : tipoClaro;
}

int Carta::getValor() const {
    return ladoOscuro ? valorOscuro : valorClaro;
}

bool Carta::esLadoOscuro() const {
    return ladoOscuro;
}
bool Carta::esJugable(const Carta& cartaSuperior) const {
    if (getColor() == cartaSuperior.getColor()) return true;
    if (getTipo() == cartaSuperior.getTipo() && getValor() == cartaSuperior.getValor()) return true;
    if (getTipo() == 2) return true; // comodín
    return false;
}
