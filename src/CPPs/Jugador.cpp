#include "Jugador.h"
#include <iostream>

Jugador::Jugador() {
    nombre = "";
    dijoUNO = false;
}

Jugador::Jugador(string nombre) {
    this->nombre = nombre;
    dijoUNO = false;
}

void Jugador::robarCarta(Mazo& mazo) {
    mano.agregarCarta(mazo.desapilar());
}

Carta Jugador::jugarCarta(int indice) {
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
