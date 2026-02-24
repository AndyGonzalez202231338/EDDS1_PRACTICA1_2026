#ifndef VISTA_CARTA_H
#define VISTA_CARTA_H

#include "Carta.h"
#include "../utils/Colores.h"
#include <iostream>
#include <string>
using namespace std;

class VistaCarta {
public:
    // Devuelve el código de color ANSI según el color de la carta
    static string obtenerColorLetra(Carta* carta);
    
    // Devuelve un símbolo representativo del color (ciruclo para colores, ★ para comodines)
    static string obtenerSimboloColor(Carta* carta);
    
    // Devuelve el texto a mostrar en la carta (número, símbolo de acción, etc.)
    static string obtenerTextoMostrar(Carta* carta);
    
    // Muestra una carta individual con su índice
    static void mostrarCartaIndividual(Carta* carta, int indice);
    
    // Muestra un conjunto de cartas en fila. osea la mano del jugador
    static void mostrarPaginaCartas(Carta** cartas, int* indices, int numCartas);
    
    // Muestra la carta que está en la mesa, la carta que va saliendo del stack
    static void mostrarCartaMesa(Carta* carta);
    
    // Muestra la información de paginación
    static void mostrarInfoPagina(int paginaActual, int totalPaginas, int totalCartas);
};

#endif