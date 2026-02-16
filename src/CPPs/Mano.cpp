#include "Mano.h"
#include <iostream>
#include <cmath>
using namespace std;

Mano::Mano() : cabeza(nullptr), cantidad(0) {}

Mano::~Mano() {
    vaciar();
}

void Mano::vaciar() {
    while (cabeza != nullptr) {
        NodoCarta* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp->dato; 
        delete temp;
    }
    cantidad = 0;
}

void Mano::agregarCarta(Carta* carta) {
    NodoCarta* nuevo = new NodoCarta(carta);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    cantidad++;
}

Carta* Mano::eliminarCarta(int indice) {
    if (cabeza == nullptr || indice < 0 || indice >= cantidad) {
        return nullptr;
    }

    if (indice == 0) {
        NodoCarta* temp = cabeza;
        Carta* carta = temp->dato;
        cabeza = temp->siguiente;
        delete temp;
        cantidad--;
        return carta;
    }

    NodoCarta* actual = cabeza;
    for (int i = 0; i < indice - 1; i++) {
        actual = actual->siguiente;
    }

    NodoCarta* temp = actual->siguiente;
    Carta* carta = temp->dato;
    actual->siguiente = temp->siguiente;
    delete temp;
    cantidad--;

    return carta;
}

Carta* Mano::obtenerCarta(int indice) const {
    if (cabeza == nullptr || indice < 0 || indice >= cantidad) {
        return nullptr;
    }

    NodoCarta* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }

    return actual->dato;
}

bool Mano::tieneCartaJugable(const Carta& cartaSuperior) const {
    NodoCarta* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato->esJugable(cartaSuperior)) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

int Mano::contarCartas() const {
    return cantidad;
}

bool debeIrAntes(const Carta* a, const Carta* b) {
    if (a->getColor() != b->getColor())
        return a->getColor() < b->getColor();
    if (a->getTipo() != b->getTipo())
        return a->getTipo() < b->getTipo();
    return a->getValor() < b->getValor();
}

void Mano::ordenar() {
    if (cabeza == nullptr || cabeza->siguiente == nullptr)
        return;

    bool cambio;
    do {
        cambio = false;
        NodoCarta* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (!debeIrAntes(actual->dato, actual->siguiente->dato)) {
                Carta* temp = actual->dato;
                actual->dato = actual->siguiente->dato;
                actual->siguiente->dato = temp;
                cambio = true;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

void Mano::mostrar() const {
    NodoCarta* actual = cabeza;
    int indice = 0;
    while (actual != nullptr) {
        cout << "[" << indice++ << "] ";
        actual->dato->mostrar();
        cout << "\n";
        actual = actual->siguiente;
    }
}

void Mano::mostrarPagina(int pagina, int cartasPorPagina) const {
    if (cabeza == nullptr || cantidad == 0) {
        cout << "  No hay cartas en la mano.\n";
        return;
    }
    
    int inicio = pagina * cartasPorPagina;
    
    // Validar página
    if (inicio >= cantidad) {
        cout << "  Página fuera de rango.\n";
        return;
    }
    
    // Calcular fin de página
    int fin = inicio + cartasPorPagina;
    if (fin > cantidad) {
        fin = cantidad;
    }
    
    // Recorrer la lista hasta llegar a la posición de inicio
    NodoCarta* actual = cabeza;
    int posicion = 0;
    
    // Avanzar hasta la posición de inicio
    while (actual != nullptr && posicion < inicio) {
        actual = actual->siguiente;
        posicion++;
    }
    
    // Mostrar las cartas de la página actual
    cout << "\n";
    while (actual != nullptr && posicion < fin) {
        cout << "  [" << posicion << "] ";
        if (actual->dato != nullptr) {
            actual->dato->mostrar();
            cout << "\n";
        }
        actual = actual->siguiente;
        posicion++;
    }
    
    cout << "\n  Página " << (pagina + 1) << " de " << getTotalPaginas(cartasPorPagina) << "\n";
}

int Mano::getTotalPaginas(int cartasPorPagina) const {
    if (cantidad == 0) return 1;
    int total = cantidad / cartasPorPagina;
    if (cantidad % cartasPorPagina != 0) {
        total++;
    }
    return total;
}