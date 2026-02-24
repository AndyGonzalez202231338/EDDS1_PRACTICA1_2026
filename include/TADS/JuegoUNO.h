#ifndef JUEGOUNO_H
#define JUEGOUNO_H

#include "Mazo.h"
#include "ListaJugadores.h"
#include "Reglas.h"

class CadenaRoboManager;
class RoboManager;

class JuegoUNO {
private:
    Mazo mazo;
    ListaJugadores jugadores;
    Reglas reglas;
    Carta* cartaSuperior;
    bool juegoActivo;
    bool modoOscuroActivo;

    int cartasRoboAcumuladas;
    bool esperandoRespuestaRobo;

    static const int CARTAS_POR_PAGINA = 7;
    string leerOpcion();

    // Métodos auxiliares
    bool procesarComando(Jugador& actual, const string& opcion, int& paginaActual, bool& turnoTerminado);
    void verificarUNO(Jugador& actual);
    bool procesarRespuestaCadena(Jugador& actual, Carta* cartaJugada);

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
    void robarCartaCastigo(Jugador& jugador);
    void manejarCantoUNO(Jugador& jugador);
    void manejarAcusarUNO(Jugador& jugador);
    void robarCartaJugadorActual();

    //========== Funciones de turno y estado del juego ==========
    void mostrarTurnos() const;
    void mostrarManos() const;
    void ejecutarTurno();
    void siguienteTurno();
    bool procesarJugada(int indice);
    bool procesarOpcionMenu(Jugador& jugador, const string& opcion, int& paginaActual, bool& turnoTerminado);
    bool juegoTerminado();
    void invertirSentido();

    //========== Metodos para acumulacion ============
    void iniciarCadenaRobo(int cantidad);
    void procesarCadenaRobo();
    bool puedeResponderRobo(const Carta& cartaJugada);
    void aplicarCastigoRobo(Jugador& jugador);

    //========== Métodos de mas 4 ============
    bool verificarSiTeniaCartaValida(Jugador& jugador);
    void manejarRetoMas4(Jugador& actual, Jugador& siguiente);

    //========== FLIP ==========
    void voltearTodasLasCartas();
    bool isModoOscuroActivo() const { return modoOscuroActivo; }
    void setModoOscuro(bool estado) { modoOscuroActivo = estado; }
    void cambiarModo();

    //========== Getters ==========
    Reglas& getReglas();
    bool getSentido();
    int getNumJugadores() const;
    Jugador& obtenerJugadorActual();
    
    void mostrarMenuTurno(Jugador& jugador);
    void limpiarJuego();
    
    friend class CadenaRoboManager;
    friend class RoboManager;
};

#endif