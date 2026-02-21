#ifndef CADENA_ROBO_MANAGER_H
#define CADENA_ROBO_MANAGER_H

#include "JuegoUNO.h"
#include "Jugador.h"
#include "Mazo.h"

class CadenaRoboManager {
private:
    int& cartasRoboAcumuladas;
    bool& esperandoRespuestaRobo;
    Carta*& cartaSuperior;
    Mazo& mazo;
    
    bool procesarRespuesta(Jugador& actual, int indice, JuegoUNO& juego);
    
public:
    CadenaRoboManager(int& acum, bool& espera, Carta*& sup, Mazo& m);
    
    void iniciarCadenaRobo(int cantidad);
    bool puedeResponderRobo(const Carta& cartaJugada) const;
    void aplicarCastigoRobo(Jugador& jugador);
    bool procesarCadenaRobo(Jugador& actual, JuegoUNO& juego);
};

#endif