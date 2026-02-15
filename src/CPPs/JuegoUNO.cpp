#include "../TADS/JuegoUNO.h"
#include <iostream>

using namespace std;

JuegoUNO::JuegoUNO() : juegoActivo(false), cartaSuperior(nullptr) {
    // Constructor
}

JuegoUNO::~JuegoUNO() {
    eliminarTodosJugadores();
    if (cartaSuperior != nullptr) {
        delete cartaSuperior;
    }
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
}

void JuegoUNO::iniciarJuego() {
    if (jugadores.size() < 2) {
        cout << "Error: Se necesitan al menos 2 jugadores para iniciar." << endl;
        return;
    }
    
    if (reglas.isModoFlipActivo()) {
        cout << "Iniciando juego en modo FLIP." << endl;
        mazo.inicializarFlip();
        mazo.imprimirMazo(); 
    } else {
        cout << "Iniciando juego en modo CLASICO." << endl;
        mazo.inicializarClasico();
        mazo.imprimirMazo();
    }

    juegoActivo = true;
    asignarTurnosAleatorios();
    mazo.barajar();
    repartirCartasIniciales();
    mostrarManos();
    mostrarTurnos();
    sacarPrimeraCarta();
    ejecutarTurno();
    ejecutarTurno();        
}

void JuegoUNO::repartirCartasIniciales() {
    const int CARTAS_INICIALES = 7;

    if (mazo.estaVacio()) {
        cout << "Error: el mazo está vacío.\n";
        return;
    }

    for (int i = 0; i < CARTAS_INICIALES; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            Jugador& jugador = const_cast<Jugador&>(jugadores.obtenerActual());
            jugador.robarCarta(mazo);
            jugadores.siguienteTurno();
        }
    }

    cout << "Cartas iniciales repartidas correctamente.\n";
}

void JuegoUNO::robarCartaJugadorActual() {
    Jugador& actual = jugadores.obtenerActual();
    actual.robarCarta(mazo);
}

bool JuegoUNO::procesarJugada(int indice) {
    Jugador& actual = jugadores.obtenerActual();
    Carta* cartaJugada = actual.jugarCarta(indice);
    
    if (cartaJugada == nullptr) {
        cout << "Error al obtener la carta.\n";
        return false;
    }
    
    if (cartaJugada->esJugable(*cartaSuperior)) {
        cout << actual.getNombre() << " juega: ";
        cartaJugada->mostrar();
        cout << "\n";
        
        
        delete cartaSuperior;
        
        
        cartaSuperior = cartaJugada;
        
        // Verificar UNO...
        if (actual.tieneUnaCarta()) {
            cout << "!" << actual.getNombre() << " tiene UNA carta. ";
            if (actual.haDichoUNO()) {
                cout << "Dijo UNO correctamente.\n";
                actual.resetearUNO();
            } else {
                cout << "¡NO DIJO UNO! Roba 2 cartas de penalización.\n";
                for (int i = 0; i < 2; i++) {
                    if (!mazo.estaVacio()) {
                        actual.robarCarta(mazo);
                    }
                }
            }
        }
        
        return true;
    } else {
        cout << "Carta no válida. Debe coincidir color o número.\n";
        // Devolver la carta a la mano
        actual.getMano().agregarCarta(cartaJugada);
        return false;
    }
}

void JuegoUNO::mostrarManos() const {
    cout << "\n============================================\n";
    cout << "MANOS INICIALES DE LOS JUGADORES\n";
    cout << "============================================\n";

    jugadores.mostrarManos();
}

void JuegoUNO::mostrarMano() {
    const Jugador& jugadorActual = jugadores.obtenerActual();
    jugadorActual.getMano().mostrar();
}

void JuegoUNO::verificarGanador() {
    cout << "Verificando si hay ganador..." << endl;
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

void JuegoUNO::sacarPrimeraCarta() {
    if (mazo.estaVacio()) {
        cout << "Error: el mazo está vacío." << endl;
        return;
    }

    cartaSuperior = mazo.desapilar();
    cout << "\nLa carta Inicial es: ";
    cartaSuperior->mostrar();
    cout << "\n" << endl;
}
void JuegoUNO::ejecutarTurno() {
    if (!juegoActivo) {
        cout << "El juego no está activo. Use 'Iniciar juego' primero." << endl;
        return;
    }
    
    Jugador& actual = jugadores.obtenerActual();
    cout << "\n=== TURNO DE " << actual.getNombre() << " ===\n";
    actual.mostrarMano();


    siguienteTurno();
}

bool JuegoUNO:: getSentido(){
    return jugadores.getSentido();
}

void JuegoUNO::invertirSentido() {
    jugadores.invertirSentido();
    cout << "Sentido invertido. Ahora es: " 
         << (jugadores.getSentido() ? "HORARIO" : "ANTIHORARIO") << endl;
}

int JuegoUNO::getNumJugadores() const {
    return jugadores.size();
}