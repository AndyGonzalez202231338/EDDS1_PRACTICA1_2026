#include "../TADS/Jugador.h"

Jugador::Jugador() {
    nombre = "";
    dijoUno = false;
}

Jugador::Jugador(string nombre) {
    this->nombre = nombre;
    dijoUno = false;
}

void Jugador::robarCarta(Mazo* mazo) {
    mano->agregarCarta(mazo->sacarCarta());
}

Carta* Jugador::jugarCarta(int indice){
    return mano->eliminarCarta(indice);
}

int Jugador::cartasEnMano() {
    return mano->contarCartas();
}

bool Jugador::tieneUNO() {
    return mano->contarCartas() == 1 && dijoUno;
}

void Jugador::cantarUno() {
    dijoUno = true;
}

string Jugador::getNombre() {
    return nombre;
}