#include "../TADS/Mano.h"

Mano::Mano() {
    cabeza = nullptr;
    tamanio = 0;
}

void Mano::agregarCarta(Carta* carta) {
    NodoCarta* nuevoNodo = new NodoCarta(carta);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
    tamanio++;
}

Carta* Mano::obtenerCarta(int indice) {
    if (indice < 0 || indice >= tamanio) {
        return nullptr; 
    }
    NodoCarta* nodoActual = cabeza;
    for (int i = 0; i < indice; i++) {
        nodoActual = nodoActual->siguiente;
    }
    return nodoActual->dato;
}

Carta* Mano::eliminarCarta(int indice) {
    if (indice < 0 || indice >= tamanio) {
        return nullptr; 
    }
    NodoCarta* nodoActual = cabeza;
    NodoCarta* nodoAnterior = nullptr;
    for (int i = 0; i < indice; i++) {
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->siguiente;
    }
    if (nodoAnterior == nullptr) {
        cabeza = nodoActual->siguiente; 
    } else {
        nodoAnterior->siguiente = nodoActual->siguiente;
    }
    Carta* cartaEliminada = nodoActual->dato;
    delete nodoActual;
    tamanio--;
    return cartaEliminada;
}

bool Mano::tieneCartaJugable(Carta* cartaSuperior) {
    NodoCarta* nodoActual = cabeza;
    while (nodoActual != nullptr) {
        if (nodoActual->dato->esJugable(cartaSuperior)) {
            return true;
        }
        nodoActual = nodoActual->siguiente;
    }
    return false;
}

int Mano::contarCartas() {
    return tamanio;
}

