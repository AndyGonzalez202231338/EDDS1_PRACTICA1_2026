#include "Mazo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

using namespace std;

Mazo::Mazo() {
    tope = nullptr;
    cantidad = 0;
}

void Mazo::apilar(const Carta& carta) {
    NodoCarta* nuevo = new NodoCarta(carta);
    nuevo->siguiente = tope;
    tope = nuevo;
    cantidad++;
}

void Mazo::inicializarFlip(int numJugadores) {
    int totalCaras = 108; // por mazo base

    Cara carasClaras[200];
    Cara carasOscuras[200];

    int totalClaro, totalOscuro;

    generarCarasClaras(carasClaras, totalClaro);
    generarCarasOscuras(carasOscuras, totalOscuro);

    barajarCaras(carasClaras, totalClaro);
    barajarCaras(carasOscuras, totalOscuro);

    int totalCartas = (numJugadores - 1) / 6 + 1;
    totalCartas *= totalClaro;

    for (int i = 0; i < totalCartas; i++) {
        Carta c(
            carasClaras[i].color, carasClaras[i].tipo, carasClaras[i].valor,
            carasOscuras[i].color, carasOscuras[i].tipo, carasOscuras[i].valor
        );
        apilar(c);
    }
}

//inicializar mazo clasico (solo caras claras)
void Mazo::inicializarClasico(int numJugadores) {
    int totalCaras = 108; // por mazo base
    Cara carasClaras[200];
    int totalClaro;
    generarCarasClaras(carasClaras, totalClaro);
    barajarCaras(carasClaras, totalClaro);
    int totalCartas = (numJugadores - 1) / 6 + 1;
    totalCartas *= totalClaro; 
    for (int i = 0; i < totalCartas; i++) {
        Carta c(
            carasClaras[i].color, carasClaras[i].tipo, carasClaras[i].valor,
            0, 0, 0 // Lado oscuro vacío
        );
        apilar(c);
    }
}



Carta Mazo::desapilar() {
    if (tope == nullptr) {
        return Carta();
    }

    NodoCarta* temp = tope;
    Carta carta = temp->dato;
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

void Mazo::generarCarasClaras(Cara* caras, int& total) {
    total = 0;

    for (int color = 0; color < 4; color++) {

        // Un solo 0
        caras[total++] = {color, 0, 0};

        // Dos cartas del 1 al 9
        for (int num = 1; num <= 9; num++) {
            caras[total++] = {color, 0, num};
            caras[total++] = {color, 0, num};
        }

        // Dos acciones
        for (int i = 0; i < 2; i++) {
            caras[total++] = {color, 1, 10}; // Skip
            caras[total++] = {color, 1, 11}; // Reverse
            caras[total++] = {color, 1, 12}; // +2
        }
    }

    // Comodines
    for (int i = 0; i < 4; i++) {
        caras[total++] = {4, 2, 13}; // +4
        caras[total++] = {4, 2, 14}; // Cambio color
    }
}


void Mazo::generarCarasOscuras(Cara* caras, int& total) {
    total = 0;

    for (int color = 0; color < 4; color++) {

        // Un solo 0
        caras[total++] = {color, 0, 0};

        // Dos cartas del 1 al 9
        for (int num = 1; num <= 9; num++) {
            caras[total++] = {color, 0, num};
            caras[total++] = {color, 0, num};
        }

        // Dos acciones por tipo (lado oscuro)
        for (int i = 0; i < 2; i++) {
            caras[total++] = {color, 1, 20}; // Skip ALL
            caras[total++] = {color, 1, 21}; // Reverse
            caras[total++] = {color, 1, 22}; // +6 (o +3 según reglas)
        }
    }

    // Comodines lado oscuro (4 y 4)
    for (int i = 0; i < 4; i++) {
        caras[total++] = {4, 2, 23}; // Wild Dark
        caras[total++] = {4, 2, 24}; // Wild +6
    }
}

void Mazo::barajarCaras(Cara* caras, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Cara temp = caras[i];
        caras[i] = caras[j];
        caras[j] = temp;
    }
}


void Mazo::imprimirMazo() const {
    cout << "\n═══════════════════════════════════════════\n";
    cout << "            MAZO DE CARTAS UNO\n";
    cout << "═══════════════════════════════════════════\n";
    
    if (tope == nullptr) {
        cout << "Mazo vacío\n";
        cout << "═══════════════════════════════════════════\n";
        return;
    }
    
    cout << "Total de cartas: " << cantidad << "\n\n";
    
    NodoCarta* actual = tope;
    int contador = 1;
    
    while (actual != nullptr) {
        cout << "Carta #" << contador++ << ":\n";
        
        // Obtener información de la carta
        Carta carta = actual->dato;
        
        // Lado actual
        cout << "  Lado: " << (carta.esLadoOscuro() ? "OSCURO" : "CLARO") << "\n";
        
        // Información del lado actual
        int color = carta.getColor();
        int tipo = carta.getTipo();
        int valor = carta.getValor();
        
        cout << "  Color: ";
        switch (color) {
            case 0: cout << "ROJO"; break;
            case 1: cout << "AMARILLO"; break;
            case 2: cout << "VERDE"; break;
            case 3: cout << "AZUL"; break;
            case 4: cout << "NEGRO (Comodín)"; break;
            default: cout << "DESCONOCIDO (" << color << ")"; break;
        }
        
        cout << "\n  Tipo: ";
        switch (tipo) {
            case 0: cout << "NÚMERO"; break;
            case 1: cout << "ACCIÓN"; break;
            case 2: cout << "COMODÍN"; break;
            default: cout << "DESCONOCIDO (" << tipo << ")"; break;
        }
        
        cout << "\n  Valor: " << valor;
        
        // Para cartas de acción, mostrar significado
        if (tipo == 1) { // TIPO_ACCION
            cout << " (";
            switch (valor) {
                case 10: cout << "SALTAR"; break;
                case 11: cout << "REVERTIR"; break;
                case 12: cout << "+2"; break;
                default: cout << "ACCIÓN ESPECIAL"; break;
            }
            cout << ")";
        }
        else if (tipo == 2) { // TIPO_COMODIN
            cout << " (";
            switch (valor) {
                case 13: cout << "+4"; break;
                case 14: cout << "CAMBIO COLOR"; break;
                default: cout << "COMODÍN ESPECIAL"; break;
            }
            cout << ")";
        }
        
        cout << "\n";
        
        // Separador entre cartas
        if (actual->siguiente != nullptr) {
            cout << "───────────────────────────────────────\n";
        }
        
        actual = actual->siguiente;
    }
    
    cout << "═══════════════════════════════════════════\n";
}




