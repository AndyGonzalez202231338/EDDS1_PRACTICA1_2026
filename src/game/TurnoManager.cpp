#include "../game/TurnoManager.h"
#include "../utils/Colores.h"
#include "../utils/InputUtils.h"
#include <iostream>
using namespace std;

void TurnoManager::mostrarInfoTurno(Jugador& jugador, Mazo& mazo, Carta* cartaSuperior) {
    cout << AMAR_BRILLANTE << "\n═══════════════════════════════════════════\n" << RESET;
    cout << BG_AMARILLO << "                  TURNO DE " << jugador.getNombre() << "         " << RESET << " \n";
    cout << AMAR_BRILLANTE << "═══════════════════════════════════════════\n" << RESET;
    cout << AMAR_BRILLANTE << "\nCartas en pila: " << BLANCO_BRIL << mazo.size() << "\n" << RESET;
    cout << AMAR_BRILLANTE << "Carta en mesa: " << RESET;
    
    if (cartaSuperior) {
        cartaSuperior->mostrar();
    } else {
        cout << "NINGUNA";
    }
    cout << "\n";
    
    if (jugador.tieneUnaCarta()) {
        cout << AMAR_BRILLANTE << "¡" << RESET << jugador.getNombre() << " tiene UNA carta!\n";
        if (!jugador.haDichoUNO()) {
            cout << ROJO_BRILLANTE << " NO HA DICHO UNO. Otros jugadores pueden acusarle.\n" << RESET;
        }
    }
}

void TurnoManager::mostrarMenuOpciones() {
    cout << CYAN_BRILLANTE << "\nOpciones:\n" << RESET;
    cout << CYAN_BRILLANTE<<"  [ÍNDICE] Jugar carta (ej: 0, 1, 2...)\n";
    cout << CYAN_BRILLANTE<<"  [N] Siguiente página\n";
    cout << CYAN_BRILLANTE<<"  [P] Página anterior\n";
    cout << CYAN_BRILLANTE<<"  [R] Robar carta\n";
    cout << CYAN_BRILLANTE<<"  [U] Cantar UNO\n";
    cout << CYAN_BRILLANTE<<"  [A] Acusar a alguien de no haber cantado UNO\n" << RESET;
}

void TurnoManager::mostrarAdvertenciaSinJugables() {
    cout << BG_ROJO << "  No tienes cartas jugables. Debes robar (R)." << RESET << "\n";
}

int TurnoManager::procesarNavegacion(char comando, int paginaActual, int totalPaginas) {
    if (comando == 'N') {
        if (paginaActual < totalPaginas - 1) {
            return paginaActual + 1;
        } else {
            cout << BG_AMARILLO << "  Ya estás en la última página.\n" << RESET;
            return paginaActual;
        }
    } else if (comando == 'P') {
        if (paginaActual > 0) {
            return paginaActual - 1;
        } else {
            cout << BG_AMARILLO << "  Ya estás en la primera página.\n" << RESET;
            return paginaActual;
        }
    }
    return paginaActual;
}