#ifndef JUEGOUNO_H
#define JUEGOUNO_H

#include "Mazo.h"
#include "ListaJugadores.h"
#include "Reglas.h"

class JuegoUNO {
private:
    Mazo mazo;
    ListaJugadores jugadores;
    Reglas reglas;
    Carta* cartaSuperior;
    bool juegoActivo;

    static const int CARTAS_POR_PAGINA = 7;

public:
    JuegoUNO();
    ~JuegoUNO();

    void agregarJugador(const string& nombre);
    void eliminarJugador(const string& nombre);
    void eliminarTodosJugadores();
    void mostrarJugadores() const;
    bool hayJugadores() const;

    void configurarJuego();
    void iniciarJuego();
    void repartirCartasIniciales();
    void verificarGanador();

    Reglas& getReglas();

    void asignarTurnosAleatorios();
    void mostrarTurnos() const;
    void mostrarManos() const;
    void mostrarMano();

    void sacarPrimeraCarta();

    void ejecutarTurno();
    void siguienteTurno();

    bool procesarJugada(int indice);
    void robarCarta();
    bool juegoTerminado();

    bool getSentido();
    void invertirSentido();
    int getNumJugadores() const;
    void robarCartaJugadorActual();

    void mostrarMenuTurno(Jugador& jugador);
    bool procesarOpcionMenu(Jugador& jugador, char opcion, int& paginaActual);
    void manejarCantoUNO(Jugador& jugador);
    void manejarAcusarUNO(Jugador& jugador);
};

#endif