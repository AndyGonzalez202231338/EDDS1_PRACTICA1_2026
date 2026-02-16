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
    string leerOpcion();

public:
    JuegoUNO();
    ~JuegoUNO();

    //========== Funciones de gestión de jugadores ==========
    void agregarJugador(const string& nombre);
    void eliminarJugador(const string& nombre);
    void eliminarTodosJugadores();
    void mostrarJugadores() const;
    bool hayJugadores() const;

    //========== Funciones de configuración y control del juego ==========
    void configurarJuego();
    void iniciarJuego();
    void repartirCartasIniciales();
    void asignarTurnosAleatorios();
    void sacarPrimeraCarta();

    //========== Funciones de jugador ==========
    void mostrarMano();
    void robarCarta();
    void manejarCantoUNO(Jugador& jugador);
    void manejarAcusarUNO(Jugador& jugador);
    void robarCartaJugadorActual();
    bool procesarOpcionMenu(Jugador& jugador, char opcion, int& paginaActual);

    //========== Funciones de turno y estado del juego ==========
    void mostrarTurnos() const;
    void mostrarManos() const;
    void ejecutarTurno();
    void siguienteTurno();
    bool procesarJugada(int indice);
    bool juegoTerminado();
    void invertirSentido();

    //========== getters
    Reglas& getReglas();
    bool getSentido();
    int getNumJugadores() const;
    
    void mostrarMenuTurno(Jugador& jugador);
    void limpiarJuego();
};

#endif