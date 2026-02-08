#ifndef JUEGOUNO_H
#define JUEGOUNO_H

#include "Mazo.h"
#include "ListaJugadores.h"
#include "Reglas.h"

class JuegoUNO {
private:
    Mazo mazo;
    ListaJugadores jugadores;
    Reglas reglas;
    Carta cartaSuperior;
    bool juegoActivo;

public:
    JuegoUNO();

    void configurarJuego();
    void iniciarJuego();
    void ejecutarTurno();
    void verificarGanador();
};

#endif