#include "../TADS/NodoJugador.h"

NodoJugador::NodoJugador(Jugador* jugador) {
    this->jugador = jugador;
    siguiente = nullptr;
}