#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador() : nombre(""), dijoUNO(false) {}

Jugador::Jugador(string nombre) : nombre(nombre), dijoUNO(false) {}

Jugador::~Jugador() {
    // Mano se destruye automáticamente y libera sus cartas
}

void Jugador::robarCarta(Mazo& mazo) {
    Carta* cartaRobada = mazo.desapilar();
    if (cartaRobada != nullptr) {
        mano.agregarCarta(cartaRobada);
    } else {
        cout << "No hay cartas en el mazo para robar.\n";
    }
}

Carta* Jugador::jugarCarta(int indice) {
    return mano.eliminarCarta(indice);
}

int Jugador::cartasEnMano() const {
    return mano.contarCartas();
}

void Jugador::mostrarMano() const {
    cout << "Mano de " << nombre << " (" << mano.contarCartas() << " cartas):\n";
    mano.mostrar();
    cout << "\n";
}

bool Jugador::tieneUnaCarta() const {
    return mano.contarCartas() == 1;
}

bool Jugador::haDichoUNO() const {
    return dijoUNO;
}

void Jugador::resetearUNO() {
    dijoUNO = false;
}

void Jugador::cantarUNO() {
    dijoUNO = true;
}

string Jugador::getNombre() const {
    return nombre;
}

Mano& Jugador::getMano() {
    return mano;
}

const Mano& Jugador::getMano() const {
    return mano;
}