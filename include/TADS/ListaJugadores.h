#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H

#include "NodoJugador.h"

class ListaJugadores {
private:
    NodoJugador* actual;
    int cantidad;
    bool sentidoHorario;

public:
    ListaJugadores();

    void agregarJugador(Jugador* jugador);
    void eliminarJugador(const string& nombre);
    void eliminarTodos();
    void mostrarJugadores() const;
    void mostrarManos() const;
    bool estaVacia() const;

    void mezclarTurnos();
    Jugador obtenerJugadorEnPosicion(int posicion);
    void setJugadorEnPosicion(int posicion, Jugador* jugador);

    void mostrarOrdenTurnos() const;

    Jugador& obtenerActual();
    void siguienteTurno();
    void invertirSentido();
    int size() const;
};

#endif
