#include "Mazo.h"
#include "CartaNumero.h"
#include "CartaAccion.h"
#include "CartaComodin.h"
#include "CartaFlip.h"
#include "CartaFlipSpecial.h"
#include "CartaX.h"
#include "CartaY.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Mazo::Mazo() : tope(nullptr), cantidad(0) {
    srand(time(nullptr));
}

Mazo::~Mazo() {
    vaciar();
}

void Mazo::vaciar() {
    while (!estaVacio()) {
        Carta* carta = desapilar();
        delete carta;
    }
}

void Mazo::apilar(Carta* carta) {
    NodoCarta* nuevo = new NodoCarta(carta);
    nuevo->siguiente = tope;
    tope = nuevo;
    cantidad++;
}

Carta* Mazo::desapilar() {
    if (tope == nullptr) {
        cout << "Mazo vacío al desapilar\n";
        return nullptr;
    }

    NodoCarta* temp = tope;
    Carta* carta = temp->dato;
    
    if (carta == nullptr) {
        delete temp;
        tope = nullptr;
        cantidad = 0;
        return nullptr;
    }
    
    
    tope = temp->siguiente;
    delete temp;
    cantidad--;

    return carta;
}

bool Mazo::estaVacio() const {
    return tope == nullptr;
}

int Mazo::size() const {
    return cantidad;
}

/*
El algoritmo que estás usando es el Fisher-Yates Shuffle (también llamado Knuth Shuffle), que es el estándar de oro para barajar.

Fases del método:
1. Pasar lista enlazada a array → O(n)
2. Aplicar Fisher-Yates → O(n)
3. Reconstruir lista enlazada → O(n)
Total: 3 * O(n) = O(n) - Lineal


Cartas (n)	 (operaciones)	Método O(n²)
108	        ~324 operaciones	~11,664
216	        ~648 operaciones	~46,656
*/
void Mazo::barajar() {
    if (tope == nullptr || tope->siguiente == nullptr) {
        return; 
    }
    
    int total = cantidad;
    NodoCarta** nodos = new NodoCarta*[total];
    
    NodoCarta* actual = tope;
    for (int i = 0; i < total; i++) {
        nodos[i] = actual;
        actual = actual->siguiente;
    }
    
    // Fisher-Yates
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        NodoCarta* temp = nodos[i];
        nodos[i] = nodos[j];
        nodos[j] = temp;
    }
    
    // Reconstruir la lista
    for (int i = 0; i < total - 1; i++) {
        nodos[i]->siguiente = nodos[i + 1];
    }
    nodos[total - 1]->siguiente = nullptr;
    
    tope = nodos[0];
    
    delete[] nodos;
}

void Mazo::imprimirMazo() const {
    cout << "\n═══════════════════════════════════════════\n";
    cout << "            MAZO DE CARTAS UNO\n";
    cout << "═══════════════════════════════════════════\n";
    
    if (tope == nullptr) {
        cout << "Mazo vacío\n";
        return;
    }
    
    cout << "Total de cartas: " << cantidad << "\n\n";
    
    NodoCarta* actual = tope;
    int contador = 1;
    
    while (actual != nullptr) {
        cout << "Carta #" << contador++ << ": ";
        actual->dato->mostrar();
        cout << "\n";
        actual = actual->siguiente;
    }
    
    cout << "═══════════════════════════════════════════\n";
}

void Mazo::agregarMazoCompleto() {
    // Guardar el tamaño actual para saber cuántas cartas había
    int tamanioActual = cantidad;
    
    // Cartas de color (4 colores)
    for (int color = 0; color < 4; color++) {
        // Un 0 por color
        apilar(new CartaNumero(color, 0));
        
        // Dos cartas del 1 al 9
        for (int num = 1; num <= 9; num++) {
            apilar(new CartaNumero(color, num));
            apilar(new CartaNumero(color, num));
        }
        
        // Dos de cada acción por color
        for (int i = 0; i < 2; i++) {
            apilar(new CartaAccion(color, 10)); // SKIP
            apilar(new CartaAccion(color, 11)); // REVERSE
            apilar(new CartaAccion(color, 12)); // +2
        }
    }
    
    // Comodines (4 de cada tipo)
    for (int i = 0; i < 4; i++) {
        apilar(new CartaComodin(13, false)); // +4
        apilar(new CartaComodin(14, false)); // CAMBIO COLOR
    }

    for (int i = 0; i < 2; i++) {
        apilar(new CartaX());      
        apilar(new CartaY()); 
    }
    
    cout << "  + Mazo agregado. Ahora hay " << (cantidad - tamanioActual) << " cartas nuevas.\n";
}

void Mazo::agregarMazoFlipCompleto() {
    int tamanioActual = cantidad;
    
    for (int color = 0; color < 4; color++) {
        apilar(new CartaFlip(color, 0, 0, color, 0, 0));
        
        for (int num = 1; num <= 9; num++) {
            apilar(new CartaFlip(color, 0, num, color, 0, num));
            apilar(new CartaFlip(color, 0, num, color, 0, num));
        }
        
        for (int i = 0; i < 2; i++) {
            apilar(new CartaFlip(color, 1, 10, color, 1, 20));
            apilar(new CartaFlip(color, 1, 11, color, 1, 21));
            apilar(new CartaFlip(color, 1, 12, color, 1, 22));
        }
    }
    
    for (int i = 0; i < 4; i++) {
        apilar(new CartaFlip(4, 2, 13, 4, 2, 23));
        apilar(new CartaFlip(4, 2, 14, 4, 2, 24));
    }
    
    for (int i = 0; i < 2; i++) {
        apilar(new CartaFlipSpecial());
    }
    
}


void Mazo::inicializarClasico(int numJugadores) {
    // Calcular número de mazos necesarios
    int numMazos = ((numJugadores - 1) / 6) + 1;
    
    vaciar();
    
    for (int m = 0; m < numMazos; m++) {
        agregarMazoCompleto();
    }
}

void Mazo::inicializarFlip(int numJugadores) {
    int numMazos = ((numJugadores - 1) / 6) + 1;
    
    vaciar();
    
    for (int m = 0; m < numMazos; m++) {
        agregarMazoFlipCompleto();
    }
}

void Mazo::inicializarClasico() {
    inicializarClasico(4); 
}
