#include "Mano.h"
#include <iostream>

using namespace std;

Mano::Mano() {
    cabeza = nullptr;
    cantidad = 0;
}

void Mano::agregarCarta(const Carta& carta) {
    NodoCarta* nuevo = new NodoCarta(carta);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    cantidad++;
}

Carta Mano::obtenerCarta(int indice) const {
    NodoCarta* actual = cabeza;
    int i = 0;

    while (actual != nullptr && i < indice) {
        actual = actual->siguiente;
        i++;
    }

    if (actual == nullptr) {
        return Carta();
    }

    return actual->dato;
}

Carta Mano::eliminarCarta(int indice) {
    if (cabeza == nullptr) {
        return Carta();
    }

    if (indice == 0) {
        NodoCarta* temp = cabeza;
        Carta carta = temp->dato;
        cabeza = temp->siguiente;
        delete temp;
        cantidad--;
        return carta;
    }

    NodoCarta* actual = cabeza;
    for (int i = 0; i < indice - 1 && actual->siguiente != nullptr; i++) {
        actual = actual->siguiente;
    }

    if (actual->siguiente == nullptr) {
        return Carta();
    }

    NodoCarta* temp = actual->siguiente;
    Carta carta = temp->dato;
    actual->siguiente = temp->siguiente;
    delete temp;
    cantidad--;

    return carta;
}

bool Mano::tieneCartaJugable(const Carta& cartaSuperior) const {
    NodoCarta* actual = cabeza;

    while (actual != nullptr) {
        if (actual->dato.esJugable(cartaSuperior)) {
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

int Mano::contarCartas() const {
    return cantidad;
}

void Mano::mostrar() const {
    NodoCarta* actual = cabeza;
    int indice = 0;

    while (actual != nullptr) {
        const Carta& c = actual->dato;

        cout << "[" << indice++ << "] ";

        // Color
        switch (c.getColor()) {
            case 0: cout << "ROJO "; break;
            case 1: cout << "AMARILLO "; break;
            case 2: cout << "VERDE "; break;
            case 3: cout << "AZUL "; break;
            case 4: cout << "NEGRO "; break;
            default: cout << "DESCONOCIDO "; break;
        }

        // Tipo y valor
        if (c.getTipo() == 0) {
            cout << c.getValor();
        } else if (c.getTipo() == 1) {
            switch (c.getValor()) {
                case 10: cout << "SALTAR"; break;
                case 11: cout << "REVERTIR"; break;
                case 12: cout << "+2"; break;
                case 20: cout << "SALTAR TODOS"; break;
                case 21: cout << "REVERTIR"; break;
                case 22: cout << "+6"; break;
                default: cout << "ACCION"; break;
            }
        } else if (c.getTipo() == 2) {
            switch (c.getValor()) {
                case 13: cout << "+4"; break;
                case 14: cout << "CAMBIO COLOR"; break;
                case 23: cout << "WILD OSCURO"; break;
                case 24: cout << "WILD +6"; break;
                default: cout << "COMODIN"; break;
            }
        }

        cout << "\n";
        actual = actual->siguiente;
    }
}
