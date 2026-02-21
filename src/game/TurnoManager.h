#ifndef TURNO_MANAGER_H
#define TURNO_MANAGER_H

#include "Jugador.h"
#include "Mazo.h"

class TurnoManager {
public:
    static void mostrarInfoTurno(Jugador& jugador, Mazo& mazo, Carta* cartaSuperior);
    static void mostrarMenuOpciones();
    static void mostrarAdvertenciaSinJugables();
    static int procesarNavegacion(char comando, int paginaActual, int totalPaginas);
    
    static const int CARTAS_POR_PAGINA = 7;
};

#endif