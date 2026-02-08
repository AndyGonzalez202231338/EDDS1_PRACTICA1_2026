#include "../TADS/Mazo.h"
#include <cstdlib>
#include <ctime>

Mazo::Mazo() {
    final = nullptr;
    tamanio = 0;
}

void Mazo::apilarCarta(Carta* carta) {
    NodoCarta* nuevoNodo = new NodoCarta(carta);
    if (final == nullptr) {
        final = nuevoNodo;
        final->siguiente = final; 
    } else {
        nuevoNodo->siguiente = final->siguiente;
        final->siguiente = nuevoNodo;
        final = nuevoNodo; 
    }
    tamanio++;
}

Carta* Mazo::sacarCarta() {
    if (final == nullptr) {
        return nullptr; 
    }
    NodoCarta* nodoASacar = final->siguiente; 
    Carta* cartaSacada = nodoASacar->dato;

    if (final == nodoASacar) {
        final = nullptr; 
    } else {
        final->siguiente = nodoASacar->siguiente;
    }
    delete nodoASacar;
    tamanio--;
    return cartaSacada;
}

bool Mazo::estaVacio() {
    return tamanio == 0;
}

int Mazo::getTamanio() {
    return tamanio;
}