#include "CartaFlipSpecial.h"
#include "../utils/Colores.h"
#include <iostream>
using namespace std;

JuegoUNO* CartaFlipSpecial::juegoActual = nullptr;

CartaFlipSpecial::CartaFlipSpecial() : Carta(4), ladoOscuro(false) {}

CartaFlipSpecial::~CartaFlipSpecial() {}

int CartaFlipSpecial::getTipo() const {
    return 3; 
}

int CartaFlipSpecial::getValor() const {
    return ladoOscuro ? 16 : 15; // 15 para FLIP, 16 para FLIP oscuro
}

void CartaFlipSpecial::mostrar() const {
    if (!ladoOscuro) {
        cout << MAGENTA_BRIL << "╔═══════╗\n";
        cout << "║ FLIP  ║\n";
        cout << "╚═══════╝" << RESET;
    } else {
        cout << GRIS_OSCURO << "╔═══════╗\n";
        cout << "║ FLIP  ║\n";
        cout << "║ DARK  ║\n";
        cout << "╚═══════╝" << RESET;
    }
}

bool CartaFlipSpecial::esJugable(const Carta& cartaSuperior) const {
    // Las cartas FLIP siempre son jugables (como comodines)
    return true;
}

void CartaFlipSpecial::ejecutarAccion(class JuegoUNO& juego) {
    cout << "\n" << MAGENTA_BRIL << "═══════════════════════════════════════════\n" << RESET;
    cout << BG_MAGENTA << "                CARTA FLIP                " << RESET << "\n";
    cout << MAGENTA_BRIL << "═══════════════════════════════════════════\n" << RESET;
    cout << "¡Se ha activado el modo FLIP!\n";
    cout << "Todas las cartas cambian de lado y se invierte el sentido.\n\n";
    
    juego.invertirSentido();
    
    juego.cambiarModo();
    
    cout << VERDE_BRILLANTE << "¡Todas las cartas han sido volteadas!\n" << RESET;
    cout << "Presiona Enter para continuar...";
    cin.get();
}

bool CartaFlipSpecial::mismoTipoYValor(const Carta& otra) const {
    return (otra.getTipo() == 3); 
}

void CartaFlipSpecial::voltear() {
    ladoOscuro = !ladoOscuro;
}

bool CartaFlipSpecial::esLadoOscuro() const {
    return ladoOscuro;
}