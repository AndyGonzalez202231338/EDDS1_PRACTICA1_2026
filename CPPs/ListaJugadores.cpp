#include "../TADS/ListaJugadores.h"

ListaJugadores::ListaJugadores() {
    actual = nullptr;
    tamanio = 0;
    sentidoHorario = true;
}

void ListaJugadores::agregarJugador(Jugador* jugador) {
    NodoJugador* nuevoNodo = new NodoJugador(jugador);
    if (actual == nullptr) {
        actual = nuevoNodo;
        actual->siguiente = actual; 
    } else {
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
        actual = nuevoNodo; 
    }
    tamanio++;
}

Jugador* ObtenerJugadorActual() {
    if (actual == nullptr) {
        return nullptr; 
    }
    return actual->jugador;
}

void ListaJugadores::siguienteTurno() {
    if (actual == nullptr) return;

    if (sentidoHorario) {
        actual = actual->siguiente;
    } else {
        NodoJugador* temp = actual;
        while (temp->siguiente != actual) {
            temp = temp->siguiente;
        }
        actual = temp;
    }
}

void ListaJugadores::invertirSentido() {
    sentidoHorario = !sentidoHorario;
}

int ListaJugadores::size() const {
    return cantidad;
}

