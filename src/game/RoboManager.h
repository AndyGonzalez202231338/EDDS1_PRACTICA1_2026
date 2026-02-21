#ifndef ROBO_MANAGER_H
#define ROBO_MANAGER_H

#include "Jugador.h"
#include "Mazo.h"
#include "Reglas.h"
#include "JuegoUNO.h"

class RoboManager {
private:
    Mazo& mazo;
    Reglas& reglas;
    Carta*& cartaSuperior;
    
public:
    RoboManager(Mazo& m, Reglas& r, Carta*& sup);
    
    // Método principal
    void robarCarta(Jugador& actual, JuegoUNO& juego);
    
    // Métodos específicos
    void robarUna(Jugador& actual, JuegoUNO& juego, bool preguntar = true); // ← CON PARÁMETRO POR DEFECTO
    void robarHastaPoder(Jugador& actual, JuegoUNO& juego);
    void robarCartaCastigo(Jugador& actual);
};

#endif