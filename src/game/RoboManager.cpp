#include "../game/RoboManager.h"
#include "../utils/Colores.h"
#include "../utils/InputUtils.h"
#include <iostream>
using namespace std;

RoboManager::RoboManager(Mazo& m, Reglas& r, Carta*& sup) 
    : mazo(m), reglas(r), cartaSuperior(sup) {}

void RoboManager::robarCarta(Jugador& actual, JuegoUNO& juego) {
    if (mazo.estaVacio()) {
        cout << ROJO_BRILLANTE << "El mazo está vacío.\n" << RESET;
        return;
    }
    
    if (reglas.isRoboHastaPoderActivo()) {
        robarHastaPoder(actual, juego);
    } else {
        robarUna(actual, juego, true);
    }
}

void RoboManager::robarUna(Jugador& actual, JuegoUNO& juego, bool preguntar) {
    Carta* cartaRobada = mazo.desapilar();
    if (!cartaRobada) return;
    
    actual.getMano().agregarCarta(cartaRobada);
    
    cout << "! Robaste: ";
    cartaRobada->mostrar();
    cout << "\n";
    
    if (preguntar && cartaRobada->esJugable(*cartaSuperior)) {
        cout << BG_VERDE << " ¿Quieres jugarla? (s/n): " << RESET;
        string respuesta = InputUtils::leerOpcion();
        if (!respuesta.empty() && toupper(respuesta[0]) == 'S') {
            for (int i = 0; i < actual.cartasEnMano(); i++) {
                if (actual.getMano().obtenerCarta(i) == cartaRobada) {
                    juego.procesarJugada(i);
                    break;
                }
            }
        }
    }
}

void RoboManager::robarHastaPoder(Jugador& actual, JuegoUNO& juego) {
    Carta* cartaRobada = nullptr;
    int cartasRobadas = 0;
    
    do {
        if (mazo.estaVacio()) {
            cout << "Mazo vacío después de " << cartasRobadas << " robos.\n";
            return;
        }
        
        cartaRobada = mazo.desapilar();
        actual.getMano().agregarCarta(cartaRobada);
        cartasRobadas++;
        
        cout << "! Robo #" << cartasRobadas << ": ";
        cartaRobada->mostrar();
        cout << "\n";
        
        if (!cartaRobada->esJugable(*cartaSuperior)) {
            if (!mazo.estaVacio()) {
                cout << "No es jugable. Robando otra...\n";
            }
        }
        
    } while (!cartaRobada->esJugable(*cartaSuperior) && !mazo.estaVacio());
    
    if (cartaRobada->esJugable(*cartaSuperior)) {
        cout << BG_VERDE << "¡Carta jugable encontrada! Se juega automáticamente." << RESET << "\n";
        juego.procesarJugada(actual.cartasEnMano() - 1);
    }
}

void RoboManager::robarCartaCastigo(Jugador& actual) {
    if (mazo.estaVacio()) {
        cout << "El mazo está vacío. No se puede robar.\n";
        return;
    }
    
    Carta* cartaRobada = mazo.desapilar();
    if (!cartaRobada) {
        cout << "Error: No se pudo robar carta.\n";
        return;
    }
    
    actual.getMano().agregarCarta(cartaRobada);
    
    cout << "! Robaste: ";
    cartaRobada->mostrar();
    cout << "\n";
}