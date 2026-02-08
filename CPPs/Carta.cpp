#include "../TADS/Carta.h"

Carta::Carta() {
    color = 0;
    tipo = 0;
    valor = 0;
    ladoOscuro = false;
}

Carta::Carta(int color, int tipo, int valor, bool ladoOscuro) {
    this->color = color;
    this->tipo = tipo;
    this->valor = valor;
    this->ladoOscuro = ladoOscuro;
}

int Carta::getColor() {
    return color;
}

int Carta::getTipo() {
    return tipo;
}

int Carta::getValor() {
    return valor;
}

bool Carta::getLadoOscuro() {
    return ladoOscuro;
}

bool Carta::esJugable(Carta* cartaSuperior) {
    if (this->ladoOscuro) {
        return false; 
    }
    if (this->color == cartaSuperior->getColor() ||
        this->tipo == cartaSuperior->getTipo() ||
        this->valor == cartaSuperior->getValor()) {
        return true;
    }
    return false;
}