#include "../TADS/JuegoUNO.h"
#include "../game/TurnoManager.h"
#include "../game/CadenaRoboManager.h"
#include "../game/RoboManager.h"
#include "../utils/Colores.h"
#include "../utils/InputUtils.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

JuegoUNO::JuegoUNO() : juegoActivo(false), cartaSuperior(nullptr), cartasRoboAcumuladas(0), esperandoRespuestaRobo(false) {}

JuegoUNO::~JuegoUNO() {
    eliminarTodosJugadores();
    delete cartaSuperior;
}

string JuegoUNO::leerOpcion() {
    return InputUtils::leerOpcion();
}

// ===== GESTIÓN DE JUGADORES =====
void JuegoUNO::agregarJugador(const string& nombre) {
    jugadores.agregarJugador(new Jugador(nombre));
    cout << VERDE_BRILLANTE<<"Jugador " << nombre << " agregado.\n"<<RESET;
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

// ===== CONFIGURACIÓN =====
void JuegoUNO::configurarJuego() {
    cout << "Configuración del juego activada.\n";
}

Reglas& JuegoUNO::getReglas() {
    return reglas;
}

// ===== INICIO DEL JUEGO =====
void JuegoUNO::iniciarJuego() {
    if (jugadores.size() < 2) {
        cout << BG_ROJO << "Error: Se necesitan al menos 2 jugadores.\n" << RESET;
        return;
    }
    
    if (reglas.isModoFlipActivo()) {
        cout << "Iniciando modo FLIP.\n";
        mazo.inicializarFlip();
    } else {
        cout << "Iniciando modo CLASICO.\n";
        mazo.inicializarClasico();
    }

    juegoActivo = true;
    asignarTurnosAleatorios();
    mazo.barajar();
    repartirCartasIniciales();
    mostrarTurnos();
    sacarPrimeraCarta();
    ejecutarTurno();
}

void JuegoUNO::repartirCartasIniciales() {
    const int CARTAS_INICIALES = 7;
    
    for (int i = 0; i < CARTAS_INICIALES; i++) {
        for (int j = 0; j < jugadores.size(); j++) {
            Jugador& jugador = const_cast<Jugador&>(jugadores.obtenerActual());
            jugador.robarCarta(mazo);
            jugadores.siguienteTurno();
        }
    }
}

void JuegoUNO::asignarTurnosAleatorios() {
    jugadores.mezclarTurnos();
}

void JuegoUNO::mostrarTurnos() const {
    cout << CYAN_BRILLANTE << "*********************************************" << RESET<< "\n";
    cout << BG_CYAN << "*    Juego con " << jugadores.size() << " jugadores " << RESET<< "\n";
    cout << CYAN_BRILLANTE << "*********************************************" << RESET<< "\n";
    jugadores.mostrarOrdenTurnos();
}

void JuegoUNO::sacarPrimeraCarta() {
    cartaSuperior = mazo.desapilar();
    
    // Si es comodín, rebarajar
    while (cartaSuperior->getTipo() == 2) {
        cout << BG_AMARILLO << "Primera carta comodín. Rebarajando...\n" << RESET;
        mazo.apilar(cartaSuperior);
        cartaSuperior = nullptr;
        mazo.barajar();
        cartaSuperior = mazo.desapilar();
    }
    
    cout << BG_VERDE << "Carta inicial: "<<RESET;
    cartaSuperior->mostrar();
    cout << "\n";
    
    if (cartaSuperior->getTipo() == 1) {
        cartaSuperior->ejecutarAccion(*this);
    }
}

// ===== EJECUCIÓN DE TURNOS =====
bool JuegoUNO::procesarOpcionMenu(Jugador& actual, const string& opcion, int& paginaActual, bool& turnoTerminado) {
    bool esNumero = true;
    for (char c : opcion) {
        if (!isdigit(c)) {
            esNumero = false;
            break;
        }
    }
    
    if (esNumero) {
        int indice = stoi(opcion);
        int totalCartas = actual.cartasEnMano();
        
        if (indice >= 0 && indice < totalCartas) {
            if (procesarJugada(indice)) {
                turnoTerminado = true;
                return true;
            }
        } else {
            cout << ROJO_BRILLANTE << "Índice inválido. Debe ser entre 0 y " << (totalCartas - 1) << "\n" << RESET;
            return true;
        }
        return true;
    } else {
        if (opcion.length() != 1) {
            cout << BG_ROJO << "Comando inválido. Use N, P, R, U, A\n" << RESET;
            return true;
        }
        return procesarComando(actual, opcion, paginaActual, turnoTerminado);
    }
}

bool JuegoUNO::procesarComando(Jugador& actual, const string& opcion, int& paginaActual, bool& turnoTerminado) {
    char c = toupper(opcion[0]);

    switch (c) {
        case 'N':
            if (paginaActual < actual.getMano().getTotalPaginas(7) - 1) {
                paginaActual++;
            } else {
                cout << BG_AMARILLO << "Última página.\n" << RESET;
            }
            break;

        case 'P':
            if (paginaActual > 0) {
                paginaActual--;
            } else {
                cout << BG_AMARILLO << "Primera página.\n" << RESET;
            }
            break;

        case 'R': {
            if (mazo.estaVacio()) {
                cout << "Mazo vacío.\n";
                break;
            }
            Carta* carta = mazo.desapilar();
            if (carta) {
                actual.getMano().agregarCarta(carta);
                cout << BG_VERDE << "Robaste: "<<RESET;
                carta->mostrar();
                cout << "\n";
            }
            turnoTerminado = true;
            break;
        }

        case 'U':
            if (actual.tieneUnaCarta()) {
                actual.cantarUNO();
                cout << BG_VERDE << "¡UNO!\n" << RESET;
            } else {
                cout << BG_ROJO << "No puedes cantar UNO.\n" << RESET;
            }
            break;
        case 'A': {
    cout << "\n=== ACUSAR POR NO DECIR UNO ===\n";
    cout << "Jugadores:\n";
    
    string nombres[10];
    NodoJugador* nodos[10];
    bool tieneUno[10];
    bool dijoUno[10];
    int total = 0;
    
    NodoJugador* temp = jugadores.getPrimerNodo();
    string nombreActual = actual.getNombre();
    
    for (int i = 0; i < jugadores.size(); i++) {
        string nombreJugador = jugadores.getNombreJugador(temp);
        
        if (nombreJugador != nombreActual) {
            nodos[total] = temp;
            nombres[total] = nombreJugador;
            tieneUno[total] = jugadores.tieneUnaCarta(temp);
            dijoUno[total] = jugadores.haDichoUNO(temp);
            
            cout << "  " << total << ". " << nombres[total];
            if (tieneUno[total]) {
                cout << VERDE_BRILLANTE" (TIENE 1 CARTA)"<<RESET;
                if (!dijoUno[total]) {
                    cout <<ROJO_BRILLANTE<< " - NO DIJO UNO"<<RESET;
                }
            }
            cout << "\n";
            total++;
        }
        temp = jugadores.getSiguienteNodo(temp);
    }
    
    if (total == 0) {
        cout << "No hay otros jugadores.\n";
        break;
    }
    
    cout << "Elige número: ";
    string entrada;
    getline(cin, entrada);
    
    if (entrada.empty()) break;
    
    int idx;
    try {
        idx = stoi(entrada);
    } catch (...) {
        cout << "Número inválido.\n";
        break;
    }
    
    if (idx < 0 || idx >= total) {
        cout << "Índice fuera de rango.\n";
        break;
    }
    
    if (tieneUno[idx] && !dijoUno[idx]) {
        cout << BG_VERDE << "Acusación válida. " << nombres[idx] << " no dijo UNO.\n" << RESET;
        cout << BG_MAGENTA<<nombres[idx] << " roba 2 cartas.\n"<<RESET;
        
        // Robar cartas al acusado
        for (int i = 0; i < 2; i++) {
            if (!mazo.estaVacio()) {
                Carta* carta = mazo.desapilar();
                if (carta) {
                    jugadores.robarCartaJugador(nodos[idx], carta);
                }
            }
        }
        // Resetear UNO del acusado
        Jugador* acusadoPtr = jugadores.getJugadorPtr(nodos[idx]);
        if (acusadoPtr != nullptr) {
            acusadoPtr->resetearUNO();
        }
    } else {
        cout << BG_ROJO << "Acusación falsa.\n" << RESET;
        cout << actual.getNombre() << " roba 2 cartas.\n";
        
        // Robar cartas al acusador (jugador actual)
        for (int i = 0; i < 2; i++) {
            if (!mazo.estaVacio()) {
                Carta* carta = mazo.desapilar();
                if (carta) {
                    const_cast<Jugador&>(actual).getMano().agregarCarta(carta);
                }
            }
        }
    }
    
    cout << "Presiona Enter...";
    cin.get();
    turnoTerminado = true;
    break;
}

    default:
            cout << BG_ROJO << "Opción inválida.\n" << RESET;
    }
    return true;
}

// ===== PROCESAMIENTO DE JUGADAS =====
bool JuegoUNO::procesarJugada(int indice) {
    Jugador& actual = jugadores.obtenerActual();
    int cartasAntes = actual.cartasEnMano();
    
    Carta* cartaJugada = actual.jugarCarta(indice);
    
    if (!cartaJugada) {
        cout << BG_ROJO << "Error al obtener carta.\n" << RESET;
        return false;
    }

    // Verificar ganar con comodín (solo si es última carta)
    if (!reglas.isGanarConNegraActivo() && cartasAntes == 1 && 
        cartaJugada->getTipo() == 2) {
        cout << BG_ROJO << "0No puedes ganar con comodín. Debes robar.\n" << RESET;
        actual.getMano().agregarCarta(cartaJugada);
        return false;
    }
    
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    
    // Si hay cadena activa, manejar respuesta
    if (esperandoRespuestaRobo && reglas.isAcumulacionActiva()) {
        return procesarRespuestaCadena(actual, cartaJugada);
    }
    
    // Jugada normal
    if (!cartaJugada->esJugable(*cartaSuperior)) {
        cout << BG_ROJO << "Carta no válida.\n" << RESET;
        actual.getMano().agregarCarta(cartaJugada);
        return false;
    }
    
    cout << BG_VERDE << actual.getNombre() << " juega: " << RESET;
    cartaJugada->mostrar();
    cout << "\n";
    
    delete cartaSuperior;
    cartaSuperior = cartaJugada;
    // elejir color si es comodin
    if (cartaJugada->getTipo() == 2) {
        cartaSuperior->ejecutarAccion(*this);
    }
    
    // Iniciar cadena si es +2 o +4
    if (reglas.isAcumulacionActiva()) {
        if (cartaJugada->getTipo() == 1 && cartaJugada->getValor() == 12) {
            cadenaManager.iniciarCadenaRobo(2);
            return true;
        } else if (cartaJugada->getTipo() == 2 && cartaJugada->getValor() == 13) {
            if (reglas.isAcumulacionActiva()) {
                cadenaManager.iniciarCadenaRobo(4);
                return true;
            } else if (reglas.isRetoMas4Activo()) {
                cout << "Se jugó un +4. El siguiente jugador puede retar.\n";
            }
        }
    }

    // Ejecutar acción si no inició cadena
    if (cartaJugada->getTipo() != 2 && !esperandoRespuestaRobo) {
        cartaSuperior->ejecutarAccion(*this);
    }
    
    // ===== AVISAR QUE TIENE 1 CARTA, PERO NO PENALIZAR =====
    if (cartasAntes == 2 && actual.cartasEnMano() == 1) {
        cout << AMAR_BRILLANTE << actual.getNombre() << " ahora tiene 1 carta. ¡NO OLVIDES CANTAR UNO!\n" << RESET;
    }
    
    return true;
}
bool JuegoUNO::procesarRespuestaCadena(Jugador& actual, Carta* cartaJugada) {
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    
    if (!cadenaManager.puedeResponderRobo(*cartaJugada)) {
        cout << ROJO_BRILLANTE << "No puedes responder con esa carta.\n" << RESET;
        actual.getMano().agregarCarta(cartaJugada);
        return false;
    }
    
    cout << BG_VERDE << actual.getNombre() << " responde: " << RESET;
    cartaJugada->mostrar();
    cout << "\n";
    
    if (cartaJugada->getTipo() == 1) {
        cartasRoboAcumuladas += 2;
    } else if (cartaJugada->getTipo() == 2) {
        cartasRoboAcumuladas += 4;
        cartaJugada->ejecutarAccion(*this);
    }
    
    cout << AZUL_BRILLANTE << "Cadena: " << cartasRoboAcumuladas << " cartas\n" << RESET;
    
    delete cartaSuperior;
    cartaSuperior = cartaJugada;
    
    return true;
}

void JuegoUNO::verificarUNO(Jugador& actual) {
    if (!actual.tieneUnaCarta()) return;
    
    // Solo verificar si la regla está activa
    if (!reglas.isGritoUNOActivo()) return;
    
    cout << actual.getNombre() << " tiene 1 carta. ";
    
    if (actual.haDichoUNO()) {
        cout << VERDE_BRILLANTE << "Dijo UNO correctamente.\n" << RESET;
        actual.resetearUNO();
    } else {
        cout << AMAR_BRILLANTE << "¡NO DIJO UNO! Roba 2 cartas.\n" << RESET;
        for (int i = 0; i < 2; i++) {
            if (!mazo.estaVacio()) {
                actual.robarCarta(mazo);
            }
        }
    }
}
// ===== MÉTODOS DE ROBO =====
void JuegoUNO::robarCarta() {
    RoboManager roboManager(mazo, reglas, cartaSuperior);
    roboManager.robarCarta(jugadores.obtenerActual(), *this);
}
void JuegoUNO::robarCartaCastigo(Jugador& jugador) {
    RoboManager roboManager(mazo, reglas, cartaSuperior);
    roboManager.robarCartaCastigo(jugador);
}
void JuegoUNO::robarCartaJugadorActual() {
    robarCarta();
}

// ===== MÉTODOS DE UNO =====
void JuegoUNO::manejarCantoUNO(Jugador& jugador) {
    if (!reglas.isGritoUNOActivo()) {
        cout << "La regla de UNO no está activa.\n";
        return;
    }
    
    if (jugador.tieneUnaCarta()) {
        jugador.cantarUNO();
        cout << VERDE_BRILLANTE << jugador.getNombre() << " grita: ¡UNO!\n" << RESET;
    } else {
        cout << BG_ROJO << "No puedes cantar UNO. Tienes " << jugador.cartasEnMano() << " cartas.\n" << RESET;
    }
}

void JuegoUNO::manejarAcusarUNO(Jugador& acusador) {
    // Verificar si la regla está activa

}
// ===== MÉTODOS DE CADENA (delegados) =====
void JuegoUNO::iniciarCadenaRobo(int cantidad) {
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    cadenaManager.iniciarCadenaRobo(cantidad);
}

void JuegoUNO::procesarCadenaRobo() {
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    cadenaManager.procesarCadenaRobo(jugadores.obtenerActual(), *this);
}

bool JuegoUNO::puedeResponderRobo(const Carta& cartaJugada) {
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    return cadenaManager.puedeResponderRobo(cartaJugada);
}

void JuegoUNO::aplicarCastigoRobo(Jugador& jugador) {
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    cadenaManager.aplicarCastigoRobo(jugador);
}

bool JuegoUNO::verificarSiTeniaCartaValida(Jugador& jugador) {
    NodoCarta* temp = nullptr;
    for (int i = 0; i < jugador.cartasEnMano(); i++) {
        Carta* carta = jugador.getMano().obtenerCarta(i);
        if (carta != nullptr) {
            if (!(carta->getTipo() == 2 && carta->getValor() == 13)) {
                if (carta->esJugable(*cartaSuperior)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void JuegoUNO::manejarRetoMas4(Jugador& actual, Jugador& siguiente) {
    cout << "=== RETO POR +4 ===\n";
    cout << siguiente.getNombre() << " está retando a " << actual.getNombre() << "\n";
    
    // Verificar si el jugador que jugó el +4 tenía otra carta válida
    bool teniaCartaValida = verificarSiTeniaCartaValida(actual);
    
    if (teniaCartaValida) {
        // Caso 1: El +4 fue usado incorrectamente
        cout << "El +4 fue usado incorrectamente. " << actual.getNombre() << " sí tenía otra carta válida.\n";
        cout << actual.getNombre() << " roba 4 cartas como castigo.\n";
        
        // El jugador que jugó el +4 roba 4 cartas
        for (int i = 0; i < 4; i++) {
            if (!mazo.estaVacio()) {
                Carta* carta = mazo.desapilar();
                if (carta) {
                    actual.getMano().agregarCarta(carta);
                }
            }
        }
        
        // El jugador que retó no roba nada
        cout << siguiente.getNombre() << " no roba cartas.\n";
        
    } else {
        // Caso 2: El +4 fue usado correctamente
        cout << "El +4 fue usado correctamente. " << actual.getNombre() << " no tenía otra opción.\n";
        cout << siguiente.getNombre() << " roba 6 cartas por retar incorrectamente.\n";
        
        // El jugador que retó roba 6 cartas (4 + 2 de penalización)
        for (int i = 0; i < 6; i++) {
            if (!mazo.estaVacio()) {
                Carta* carta = mazo.desapilar();
                if (carta) {
                    siguiente.getMano().agregarCarta(carta);
                }
            }
        }
    }
    
    cout << "Presiona Enter para continuar...";
    cin.get();
}

// ===== ESTADO DEL JUEGO =====
bool JuegoUNO::juegoTerminado() {
    return jugadores.obtenerActual().cartasEnMano() == 0;
}

void JuegoUNO::siguienteTurno() {
    jugadores.siguienteTurno();
}

void JuegoUNO::invertirSentido() {
    jugadores.invertirSentido();
    cout << BG_MAGENTA << "Sentido: " << (jugadores.getSentido() ? "HORARIO" : "ANTIHORARIO") << "\n" << RESET;
}

bool JuegoUNO::getSentido() {
    return jugadores.getSentido();
}

int JuegoUNO::getNumJugadores() const {
    return jugadores.size();
}

void JuegoUNO::limpiarJuego() {
    for (int i = 0; i < jugadores.size(); i++) {
        Jugador& j = jugadores.obtenerJugadorEnPosicionModificable(i);
        while (j.cartasEnMano() > 0) {
            delete j.jugarCarta(0);
        }
        j.resetearUNO();
    }
    mazo.vaciar();
    delete cartaSuperior;
    cartaSuperior = nullptr;
    juegoActivo = false;
    cartasRoboAcumuladas = 0;
    esperandoRespuestaRobo = false;
}

void JuegoUNO::ejecutarTurno() {
    if (!juegoActivo) return;
    
    CadenaRoboManager cadenaManager(cartasRoboAcumuladas, esperandoRespuestaRobo, cartaSuperior, mazo);
    RoboManager roboManager(mazo, reglas, cartaSuperior);
    
    while (juegoActivo && !juegoTerminado()) {
        Jugador& actual = jugadores.obtenerActual();
        
        if (esperandoRespuestaRobo && reglas.isAcumulacionActiva()) {
            bool cadenaSigue = cadenaManager.procesarCadenaRobo(actual, *this);
            if (!cadenaSigue) {
                InputUtils::pausa();
                InputUtils::limpiarPantalla();
                siguienteTurno();
            }
            continue;
        }
        
        // Turno normal
        TurnoManager::mostrarInfoTurno(actual, mazo, cartaSuperior);
        
        int paginaActual = 0;
        bool turnoTerminado = false;
        bool acabaDeJugar = false;
        
        while (!turnoTerminado && juegoActivo) {
            actual.getMano().mostrarPagina(paginaActual, TurnoManager::CARTAS_POR_PAGINA);
            TurnoManager::mostrarMenuOpciones();
            
            if (!actual.getMano().tieneCartaJugable(*cartaSuperior)) {
                TurnoManager::mostrarAdvertenciaSinJugables();
            }
            
            cout << BG_CYAN << "Elige: " << RESET;
            string opcion = leerOpcion();
            
            int cartasAntes = actual.cartasEnMano();
            
            procesarOpcionMenu(actual, opcion, paginaActual, turnoTerminado);
            
            bool esNumero = true;
            for (char c : opcion) {
                if (!isdigit(c)) {
                    esNumero = false;
                    break;
                }
            }

            if (esNumero && turnoTerminado) {
                if (actual.tieneUnaCarta() && cartasAntes == 2) {
                    acabaDeJugar = true;
                    turnoTerminado = false;
                    
                    cout << AMAR_BRILLANTE << "\nTienes 1 carta. ¿Quieres cantar UNO? (s/n): " << RESET;
                    string respuesta = InputUtils::leerOpcion();
                    if (!respuesta.empty() && toupper(respuesta[0]) == 'S') {
                        manejarCantoUNO(actual);
                    }
                    turnoTerminado = true;
                    break;
                } else {
                    turnoTerminado = true;
                }
            }
            
            if (actual.cartasEnMano() == 0) {
                cout << VERDE_BRILLANTE << "\n ¡" << actual.getNombre() << " GANA! \n" << RESET;
                limpiarJuego();
                juegoActivo = false;
                cout << "Presiona Enter para volver al menú principal...";
                cin.get();

                break;
            }
        }
        if (juegoActivo && !esperandoRespuestaRobo && turnoTerminado) {
            InputUtils::limpiarPantalla();
            siguienteTurno();
        }
    }
}

Jugador& JuegoUNO::obtenerJugadorActual() {
    return jugadores.obtenerActual();
}
void JuegoUNO::mostrarMenuTurno(Jugador&) {}
void JuegoUNO::mostrarManos() const { jugadores.mostrarManos(); }
void JuegoUNO::mostrarMano() { jugadores.obtenerActual().getMano().mostrar(); }