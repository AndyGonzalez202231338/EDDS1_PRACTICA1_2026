#include "Mano.h"
#include "VistaCarta.h"
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

/*
Este método implementa el algoritmo Bubble Sort (Ordenamiento Burbuja) pero sobre un array de punteros a nodos.
Complejidad: O(n²) - Cuadrática


Cantidad de cartas (n)	Operaciones aproximadas
7	~49 comparaciones
15	~225 comparaciones
30	~900 comparaciones
*/
void Mano::ordenar() {
    if (cabeza == nullptr || cabeza->siguiente == nullptr)
        return;
    
    int total = cantidad;
    NodoCarta** nodos = new NodoCarta*[total];
    
    // Llenar el arreglo con los nodos en orden actual
    NodoCarta* actual = cabeza;
    for (int i = 0; i < total; i++) {
        nodos[i] = actual;
        actual = actual->siguiente;
    }
    
    // Ordenando arreglo por colores y numeros
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            Carta* a = nodos[j]->dato;
            Carta* b = nodos[j + 1]->dato;
            
            bool debenIntercambiarse = false;
            
            // Comparar por color
            if (a->getColor() > b->getColor()) {
                debenIntercambiarse = true;
            }
            // Mismo color, comparar por tipo
            else if (a->getColor() == b->getColor()) {
                if (a->getTipo() > b->getTipo()) {
                    debenIntercambiarse = true;
                }
                // Mismo color y tipo, comparar por valor
                else if (a->getTipo() == b->getTipo()) {
                    if (a->getValor() > b->getValor()) {
                        debenIntercambiarse = true;
                    }
                }
            }
            
            if (debenIntercambiarse) {
                NodoCarta* temp = nodos[j];
                nodos[j] = nodos[j + 1];
                nodos[j + 1] = temp;
            }
        }
    }
    
    // Reconstruir la lista enlazada con el orden
    cabeza = nodos[0];
    for (int i = 0; i < total - 1; i++) {
        nodos[i]->siguiente = nodos[i + 1];
    }
    nodos[total - 1]->siguiente = nullptr;
    
    delete[] nodos;
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
    
    if (inicio >= cantidad) {
        cout << "  Página fuera de rango.\n";
        return;
    }
    
    int fin = inicio + cartasPorPagina;
    if (fin > cantidad) {
        fin = cantidad;
    }
    
    NodoCarta* actual = cabeza;
    int posicion = 0;
    
    while (actual != nullptr && posicion < inicio) {
        actual = actual->siguiente;
        posicion++;
    }
    
    const int MAX_PAGINA = 10;
    Carta* cartasPagina[MAX_PAGINA];
    int indices[MAX_PAGINA];
    int numCartas = 0;
    
    while (actual != nullptr && posicion < fin && numCartas < MAX_PAGINA) {
        if (actual->dato != nullptr) {
            cartasPagina[numCartas] = actual->dato;
            indices[numCartas] = posicion;
            numCartas++;
        }
        actual = actual->siguiente;
        posicion++;
    }
    
    cout << "\n";
    VistaCarta::mostrarPaginaCartas(cartasPagina, indices, numCartas);
    
    int totalPaginas = (cantidad + cartasPorPagina - 1) / cartasPorPagina;
    VistaCarta::mostrarInfoPagina(pagina, totalPaginas, cantidad);
}

int Mano::getTotalPaginas(int cartasPorPagina) const {
    if (cantidad == 0) return 1;
    int total = cantidad / cartasPorPagina;
    if (cantidad % cartasPorPagina != 0) {
        total++;
    }
    return total;
}


