#include "../game/CadenaRoboManager.h"
#include "../utils/Colores.h"
#include "../utils/InputUtils.h"
#include <iostream>
using namespace std;

CadenaRoboManager::CadenaRoboManager(int& acum, bool& espera, Carta*& sup, Mazo& m)
    : cartasRoboAcumuladas(acum), esperandoRespuestaRobo(espera), 
      cartaSuperior(sup), mazo(m) {}

void CadenaRoboManager::iniciarCadenaRobo(int cantidad) {
    cartasRoboAcumuladas = cantidad;
    esperandoRespuestaRobo = true;
    cout << AZUL_BRILLANTE << "\n ¡CADENA DE ROBO INICIADA!" << RESET<< "\n";
    cout << "Cartas acumuladas: " << cartasRoboAcumuladas << "\n";
    
    if (cartaSuperior != nullptr) {
        if (cartaSuperior->getTipo() == 1 && cartaSuperior->getValor() == 12) {
            cout << "Tipo: +2 (solo se puede responder con +2)\n";
        } else if (cartaSuperior->getTipo() == 2 && cartaSuperior->getValor() == 13) {
            cout << "Tipo: +4 (solo se puede responder con +4)\n";
        }
    }
}

bool CadenaRoboManager::puedeResponderRobo(const Carta& cartaJugada) const {
    if (!esperandoRespuestaRobo || cartaSuperior == nullptr) return false;
    
    int tipoSuperior = cartaSuperior->getTipo();
    int valorSuperior = cartaSuperior->getValor();
    
    // Cadena de +2
    if (tipoSuperior == 1 && valorSuperior == 12) {
        return (cartaJugada.getTipo() == 1 && cartaJugada.getValor() == 12);
    }
    
    // Cadena de +4
    if (tipoSuperior == 2 && valorSuperior == 13) {
        return (cartaJugada.getTipo() == 2 && cartaJugada.getValor() == 13);
    }
    
    return false;
}

void CadenaRoboManager::aplicarCastigoRobo(Jugador& jugador) {
    cout << BG_ROJO << " ¡CASTIGO APLICADO! \n" << RESET;
    cout << jugador.getNombre() << " roba " << cartasRoboAcumuladas << " cartas\n";
    
    for (int i = 0; i < cartasRoboAcumuladas; i++) {
        if (!mazo.estaVacio()) {
            jugador.robarCarta(mazo);
        } else {
            cout << " El mazo se vació\n";
            break;
        }
    }
    
    cartasRoboAcumuladas = 0;
    esperandoRespuestaRobo = false;
}

bool CadenaRoboManager::procesarCadenaRobo(Jugador& actual, JuegoUNO& juego) {
    if (!esperandoRespuestaRobo) return false;
    
    cout << ROJO_BRILLANTE << "\n═══════════════════════════════════════════" << RESET<< "\n";
    cout << BG_ROJO << "         CADENA DE ROBO - " << actual.getNombre() << "         " << RESET << "\n";
    cout << ROJO_BRILLANTE << "═══════════════════════════════════════════" << RESET<< "\n";
    cout << "Cartas acumuladas: " << cartasRoboAcumuladas << "\n\n";
    
    // Mostrar mano del jugador
    actual.getMano().mostrarPagina(0, 7);
    
    cout << "\nOpciones:\n";
    cout << "  [ÍNDICE] Jugar ";
    if (cartaSuperior != nullptr) {
        if (cartaSuperior->getTipo() == 1 && cartaSuperior->getValor() == 12) {
            cout << "+2";
        } else if (cartaSuperior->getTipo() == 2 && cartaSuperior->getValor() == 13) {
            cout << "+4";
        }
    }
    cout << "\n";
    cout << CYAN_BRILLANTE << "  [R] Robar las " << cartasRoboAcumuladas << " cartas\n";
    cout << BG_CYAN << "Elige: " << RESET;
    
    string opcion = InputUtils::leerOpcion();
    
    try {
        int indice = stoi(opcion);
        Carta* carta = actual.getMano().obtenerCarta(indice);
        
        if (carta && puedeResponderRobo(*carta)) {
            return procesarRespuesta(actual, indice, juego);
        } else {
            cout << ROJO_BRILLANTE << " No puedes responder con esa carta\n" << RESET;
        }
    } catch (...) {
        if (opcion.length() == 1 && toupper(opcion[0]) == 'R') {
            aplicarCastigoRobo(actual);
            return false; // Cadena terminó
        }
    }
    return true; // Cadena sigue activa
}

bool CadenaRoboManager::procesarRespuesta(Jugador& actual, int indice, JuegoUNO& juego) {
    Carta* cartaJugada = actual.jugarCarta(indice);
    
    cout << VERDE_BRILLANTE << actual.getNombre() << " responde con: " << RESET;
    cartaJugada->mostrar();
    cout << "\n";
    
    // Acumular más cartas
    if (cartaJugada->getTipo() == 1) { // +2
        cartasRoboAcumuladas += 2;
    } else if (cartaJugada->getTipo() == 2) { // +4
        cartasRoboAcumuladas += 4;
        cartaJugada->ejecutarAccion(juego);
    }
    
    cout << AMAR_BRILLANTE << "⚡ Cadena aumentada a " << cartasRoboAcumuladas << " cartas\n" << RESET;
    
    delete cartaSuperior;
    cartaSuperior = cartaJugada;
    
    return true; // Cadena sigue activa
}