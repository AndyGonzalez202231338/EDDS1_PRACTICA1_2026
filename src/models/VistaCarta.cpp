#include <typeinfo>
#include "CartaFlip.h"
#include "CartaFlipSpecial.h"
#include "VistaCarta.h"

string VistaCarta::obtenerColorLetra(Carta* carta) {
    if (carta == nullptr) return RESET;
    
    int color = carta->getColor();
    
    switch (color) {
        case 0: return ROJO;           // Rojo
        case 1: return AMARILLO;        // Amarillo
        case 2: return VERDE;           // Verde
        case 3: return AZUL;            // Azul
        case 4: return rosado;          // Rosa (nuevo)
        case 5: return violeta;         // Violeta (nuevo)
        case 6: return naranja;         // Naranja (nuevo)
        case 7: return CYAN_BRILLANTE;  // Celeste/Turquesa
        case 8: return BLANCO;          // Blanco (comodines)
        default: return RESET;
    }
}

string VistaCarta::obtenerSimboloColor(Carta* carta) {
    if (carta == nullptr) return "?";

    if (carta->getValor() == 15) return "X";
    if (carta->getValor() == 25) return "Y";
    
    // Si es carta FLIP especial
    if (carta->getTipo() == 3) {
        return "F";
    }
    
    // Si es comodín (tipo 2)
    if (carta->getTipo() == 2) {
        return "★";
    }
    
    // Si es una carta FLIP normal
    CartaFlip* flip = dynamic_cast<CartaFlip*>(carta);
    if (flip != nullptr) {
        if (flip->esLadoOscuro()) {
            return "◉";  // Círculo relleno para oscuro
        } else {
            return "○";  // Círculo vacío para claro
        }
    }
    
    return "○";
}

string VistaCarta::obtenerTextoMostrar(Carta* carta) {
    if (carta == nullptr) return "?";
    if (carta->getValor() == 15) return "X";
    if (carta->getValor() == 25) return "Y";
    
    // Si es carta FLIP especial
    if (carta->getTipo() == 3) {
        CartaFlipSpecial* flipSpecial = dynamic_cast<CartaFlipSpecial*>(carta);
        if (flipSpecial != nullptr && flipSpecial->esLadoOscuro()) {
            return "DK";
        }
        return "FL";
    }
    
    if (carta->getTipo() == 0) {
        return to_string(carta->getValor());
    } else if (carta->getTipo() == 1) {
        switch (carta->getValor()) {
            case 10: return "S";
            case 11: return "R";
            case 12: return "+2";
            case 20: return "SA";
            case 21: return "R";
            case 22: return "+6";
            default: return "?";
        }
    } else if (carta->getTipo() == 2) {
        switch (carta->getValor()) {
            case 13: return "+4";
            case 14: return "C";
            case 23: return "WD";
            case 24: return "W6";
            default: return "?";
        }
    }
    return "?";
}

void VistaCarta::mostrarCartaIndividual(Carta* carta, int indice) {
    if (carta == nullptr) return;
    
    string color = obtenerColorLetra(carta);
    string simbolo = obtenerSimboloColor(carta);
    string texto = obtenerTextoMostrar(carta);
    
    if (indice < 10) {
        cout << "   [ " << indice << " ]   ";
    } else {
        cout << "  [ " << indice << " ]  ";
    }
    cout << "\n";
    
    cout << color << "  ╭─────╮  " << RESET << "\n";
    cout << color << "  │  " << simbolo << "  │  " << RESET << "\n";
    cout << color << "  │";
    if (texto.length() == 1) {
        cout << "  " << texto << "  ";
    } else if (texto.length() == 2) {
        cout << " " << texto << "  ";
    } else {
        cout << " " << texto << " ";
    }
    cout << "│  " << RESET << "\n";
    cout << color << "  │     │  " << RESET << "\n";
    cout << color << "  ╰─────╯  " << RESET << "\n";
}

void VistaCarta::mostrarPaginaCartas(Carta** cartas, int* indices, int numCartas) {
    if (numCartas == 0) return;
    
    for (int i = 0; i < numCartas; i++) {
        if (indices[i] < 10) {
            cout << "   [ " << indices[i] << " ]   ";
        } else {
            cout << "  [ " << indices[i] << " ]  ";
        }
    }
    cout << "\n";
    
    for (int i = 0; i < numCartas; i++) {
        cout << obtenerColorLetra(cartas[i]) << "  ╭─────╮  " << RESET;
    }
    cout << "\n";
    
    for (int i = 0; i < numCartas; i++) {
        cout << obtenerColorLetra(cartas[i]) << "  │  " 
             << obtenerSimboloColor(cartas[i]) << "  │  " << RESET;
    }
    cout << "\n";
    
    for (int i = 0; i < numCartas; i++) {
        string texto = obtenerTextoMostrar(cartas[i]);
        cout << obtenerColorLetra(cartas[i]) << "  │";
        
        if (texto.length() == 1) {
            cout << "  " << texto << "  ";
        } else if (texto.length() == 2) {
            cout << " " << texto << "  ";
        } else {
            cout << " " << texto << " ";
        }
        
        cout << "│  " << RESET;
    }
    cout << "\n";
    
    for (int i = 0; i < numCartas; i++) {
        cout << obtenerColorLetra(cartas[i]) << "  │     │  " << RESET;
    }
    cout << "\n";
    
    for (int i = 0; i < numCartas; i++) {
        cout << obtenerColorLetra(cartas[i]) << "  ╰─────╯  " << RESET;
    }
    cout << "\n";
}

void VistaCarta::mostrarCartaMesa(Carta* carta) {
    if (carta == nullptr) {
        cout << "  No hay carta en mesa\n";
        return;
    }
    
    string color = obtenerColorLetra(carta);
    string simbolo = obtenerSimboloColor(carta);
    string texto = obtenerTextoMostrar(carta);
    
    cout << "\n" << AMAR_BRILLANTE << "Carta en mesa: " << RESET << "\n";
    
    cout << color << "  ╭─────╮  " << RESET << "\n";
    cout << color << "  │  " << simbolo << "  │  " << RESET << "\n";
    cout << color << "  │";
    if (texto.length() == 1) {
        cout << "  " << texto << "  ";
    } else if (texto.length() == 2) {
        cout << " " << texto << "  ";
    } else {
        cout << " " << texto << " ";
    }
    cout << "│  " << RESET << "\n";
    cout << color << "  │     │  " << RESET << "\n";
    cout << color << "  ╰─────╯  " << RESET << "\n";
}

void VistaCarta::mostrarInfoPagina(int paginaActual, int totalPaginas, int totalCartas) {
    cout << "\n  Página " << (paginaActual + 1) << " de " << totalPaginas;
    cout << " (" << totalCartas << " cartas totales)\n";
}