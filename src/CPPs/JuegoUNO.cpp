#include "../TADS/JuegoUNO.h"
#include <iostream>

using namespace std;

JuegoUNO::JuegoUNO() : juegoActivo(false) {
    // Constructor
}

JuegoUNO::~JuegoUNO() {
    eliminarTodosJugadores();
}

void JuegoUNO::agregarJugador(const string& nombre) {
    Jugador* nuevoJugador = new Jugador(nombre);  
    jugadores.agregarJugador(nuevoJugador);       
    
    cout << "Jugador " << nombre << " agregado exitosamente." << endl;
}


void JuegoUNO::eliminarJugador(const string& nombre) {
    jugadores.eliminarJugador(nombre);
}

void JuegoUNO::eliminarTodosJugadores() {
    jugadores.eliminarTodos();
}

void JuegoUNO::mostrarJugadores() const {
    jugadores.mostrarJugadores();
}

bool JuegoUNO::hayJugadores() const {
    return !jugadores.estaVacia();
}


void JuegoUNO::configurarJuego() {
    cout << "Configuración del juego activada." << endl;
    // Aquí deberías tener lógica para configurar reglas específicas
    // Por ahora es un placeholder
}

void JuegoUNO::iniciarJuego() {
    if (jugadores.size() < 2) {
        cout << "Error: Se necesitan al menos 2 jugadores para iniciar." << endl;
        return;
    }
    
    if (reglas.isModoFlipActivo()) {
        cout << "Iniciando juego en modo FLIP." << endl;
        mazo.inicializarFlip(jugadores.size());
        mazo.imprimirMazo(); // Mostrar el mazo completo para verificar que se generó correctamente
    } else {
        cout << "Iniciando juego en modo CLASICO." << endl;
        mazo.inicializarClasico(jugadores.size());
        mazo.imprimirMazo(); // Mostrar el mazo completo para verificar que se generó correctamente
    }

    juegoActivo = true;
    asignarTurnosAleatorios();
    repartirCartasIniciales();
    mostrarManos();
    mostrarTurnos();


}

void JuegoUNO::repartirCartasIniciales() {
    const int CARTAS_INICIALES = 7;

    if (mazo.estaVacio()) {
        cout << "Error: el mazo está vacío.\n";
        return;
    }

    for (int i = 0; i < CARTAS_INICIALES; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            Jugador& jugador = jugadores.obtenerActual();
            jugador.robarCarta(mazo);
            jugadores.siguienteTurno();
        }
    }

    cout << "Cartas iniciales repartidas correctamente.\n";
}

void JuegoUNO::mostrarManos() const {
    cout << "\n============================================\n";
    cout << "MANOS INICIALES DE LOS JUGADORES\n";
    cout << "============================================\n";

    jugadores.mostrarManos();
}

void JuegoUNO::verificarGanador() {
    cout << "Verificando si hay ganador..." << endl;
    // Lógica para verificar ganador aquí
}

Reglas& JuegoUNO::getReglas() {
    return reglas;
}

void JuegoUNO::asignarTurnosAleatorios() {
    jugadores.mezclarTurnos();
}

void JuegoUNO::mostrarTurnos() const {
    cout << "*************************************************************\n";
    cout << "El juego ha iniciado con " << jugadores.size() << " jugadores\n";
    cout << "*************************************************************\n";
    jugadores.mostrarOrdenTurnos();
}

void JuegoUNO::siguienteTurno() {
    jugadores.siguienteTurno();
}

Jugador& JuegoUNO::obtenerActual() {
    return jugadores.obtenerActual();
}

void JuegoUNO::ejecutarTurno() {
    if (!juegoActivo) {
        cout << "El juego no está activo. Use 'Iniciar juego' primero." << endl;
        return;
    }
    
    Jugador& actual = obtenerActual();
    cout << "\n=== TURNO DE " << actual.getNombre() << " ===\n";
    
    // Mostrar carta superior
    // cout << "Carta superior: " << cartaSuperior.toString() << endl;
    
    // Mostrar mano del jugador
    // actual.getMano()->mostrar();
    
    // Lógica del turno...
    
    // Pasar al siguiente turno
    siguienteTurno();
}