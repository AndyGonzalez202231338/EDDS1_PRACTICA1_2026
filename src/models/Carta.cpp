#include "Carta.h"

Carta::Carta(int color) : color(color), ladoOscuro(false) {}

Carta::~Carta() {}

int Carta::getColor() const {
    return color;
}

bool Carta::esJugable(const Carta& cartaSuperior) const {
    return (getColor() == cartaSuperior.getColor() || mismoTipoYValor(cartaSuperior) ||
        esComodin());
}

void Carta::voltear() {
    ladoOscuro = !ladoOscuro;
}

bool Carta::esLadoOscuro() const {
    return ladoOscuro;
}

bool Carta::esComodin() const {
    return false;
}