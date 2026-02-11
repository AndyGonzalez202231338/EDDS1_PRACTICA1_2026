#ifndef MENU_H
#define MENU_H

#include "JuegoUNO.h"

class Menu {
private:
    JuegoUNO juego;

    void mostrarMenuPrincipal();
    void menuConfiguracion();
    void menuJugadores();
    void mostrarEstado(bool estado);
    void mostrarTurnoActual();

public:
    Menu();
    void iniciar();
    int obtenerEnteroValido(int min, int max);
};

#endif
