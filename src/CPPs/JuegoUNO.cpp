#include "../TADS/JuegoUNO.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

#define RESET   "\033[0m"

#define NEGRO   "\033[30m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BLANCO  "\033[37m"

#define GRIS_OSCURO     "\033[90m"
#define ROJO_BRILLANTE  "\033[91m"
#define VERDE_BRILLANTE "\033[92m"
#define AMAR_BRILLANTE  "\033[93m"
#define AZUL_BRILLANTE  "\033[94m"
#define MAGENTA_BRIL    "\033[95m"
#define CYAN_BRILLANTE  "\033[96m"
#define BLANCO_BRIL     "\033[97m"

#define BG_ROJO     "\033[41m"
#define BG_VERDE    "\033[42m"
#define BG_AMARILLO "\033[43m"
#define BG_AZUL     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_BLANCO   "\033[47m"

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
    //mostrarManos();
    mostrarTurnos();
    sacarPrimeraCarta();
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
}

void JuegoUNO::ejecutarTurno() {
    if (!juegoActivo) {
        cout << "El juego no está activo. Use 'Iniciar juego' primero." << endl;
        return;
    }
    
    while (juegoActivo && !juegoTerminado()) {
        Jugador& actual = jugadores.obtenerActual();
        
        cout <<AMAR_BRILLANTE<< "\n═══════════════════════════════════════════\n"<<RESET;
        cout <<BG_AMARILLO<< "                  TURNO DE " << actual.getNombre()<<"         "<<RESET << " \n";
        cout <<AMAR_BRILLANTE<< "═══════════════════════════════════════════\n"<<RESET;
        cout <<AMAR_BRILLANTE<< "\nCartas en pila: "<<BLANCO_BRIL<< mazo.size() << "\n"<<RESET;
        cout <<AMAR_BRILLANTE<< "Carta en mesa: "<<RESET;
        if (cartaSuperior) {
            cartaSuperior->mostrar();
        } else {
            cout << "NINGUNA";
        }
        cout << "\n";
        
        if (actual.tieneUnaCarta()) {
            cout <<AMAR_BRILLANTE<< "!"<<RESET<< actual.getNombre() << " tiene UNA carta!\n";
            if (!actual.haDichoUNO()) {
                cout <<ROJO_BRILLANTE<< "!"<<RESET<< " NO HA DICHO UNO. Otros jugadores pueden acusarle.\n";
            }
        }
        
        // Mostrar menú principal del turno
        int paginaActual = 0;
        bool turnoTerminado = false;
        
        while (!turnoTerminado) {
            
            // Mostrar cartas de la página actual
            cout <<VERDE_BRILLANTE<< "\n--- Tus cartas (página " <<RESET<<(paginaActual + 1)<<VERDE_BRILLANTE 
                 << " de " <<RESET<< actual.getMano().getTotalPaginas(CARTAS_POR_PAGINA) << ") "<<VERDE_BRILLANTE<<"---\n"<<RESET;
            actual.getMano().mostrarPagina(paginaActual, CARTAS_POR_PAGINA);
            
            cout <<CYAN_BRILLANTE <<"\nOpciones:\n";
            cout << "  [ÍNDICE] Jugar carta (ej: 0, 1, 2...)\n";
            cout << "  [N] Siguiente página\n";
            cout << "  [P] Página anterior\n";
            cout << "  [R] Robar carta\n";
            cout << "  [U] Cantar UNO\n";
            cout << "  [A] Acusar a alguien de no haber cantado UNO\n"<<RESET;
            
            if (!actual.getMano().tieneCartaJugable(*cartaSuperior)) {
                cout <<BG_ROJO<< "!" <<"No tienes cartas jugables. Debes robar (R)."<<RESET<<"\n";
            }
            
            cout <<BG_CYAN<< "Elige: "<<RESET;
            
            string opcion;
            cin >> opcion;
            
            // PRIMERO: Intentar interpretar como número (índice de carta)
            try {
                int indice = stoi(opcion);
                if (indice >= 0 && indice < actual.cartasEnMano()) {
                    if (procesarJugada(indice)) {
                        turnoTerminado = true;
                    }
                } else {
                    cout <<ROJO_BRILLANTE<< "X" <<ROJO_BRILLANTE<< " Índice inválido. Debe ser entre 0 y " <<RESET<< (actual.cartasEnMano() - 1) << ".\n";
                }
            } 
            catch (const invalid_argument&) {
                // SEGUNDO: Si no es número, verificar comandos de letra
                if (opcion.length() == 1) {
                    char c = toupper(opcion[0]);
                    
                    switch (c) {
                        case 'N': // Siguiente página
                            if (paginaActual < actual.getMano().getTotalPaginas(CARTAS_POR_PAGINA) - 1) {
                                paginaActual++;
                            } else {
                                cout <<BG_AMARILLO<< "!" <<AMAR_BRILLANTE<< " Ya estás en la última página."<<RESET<<"\n";
                            }
                            break;
                            
                        case 'P': // Página anterior
                            if (paginaActual > 0) {
                                paginaActual--;
                            } else {
                                cout <<BG_AMARILLO<< "!" <<AMAR_BRILLANTE<< " Ya estás en la primera página."<<RESET<<"\n";
                            }
                            break;
                            
                        case 'R': // Robar carta
                            robarCarta();
                            turnoTerminado = true;
                            break;
                            
                        case 'U': // Cantar UNO
                            manejarCantoUNO(actual);
                            break;
                            
                        case 'A': // Acusar UNO
                            manejarAcusarUNO(actual);
                            break;
                            
                        default:
                            cout <<BG_ROJO<< "X" <<RESET<< " Opción inválida.\n";
                    }
                } else {
                    cout <<BG_ROJO<< "X" <<RESET<< " Opción inválida.\n";
                }
            }
            catch (const out_of_range&) {
                cout <<BG_ROJO<< "X" <<RESET<< " Número demasiado grande.\n";
            }
        }
        
        // Verificar si alguien ganó
        if (juegoTerminado()) {
            cout << "\n ¡" << jugadores.obtenerActual().getNombre() 
                 << " ha ganado la partida! \n";
            juegoActivo = false;
            break;
        }
        
        // Avanzar al siguiente turno
        siguienteTurno();
        
        cout <<VERDE_BRILLANTE <<"\nPresiona Enter para continuar..."<<RESET;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        system("clear");
    }
}

void JuegoUNO::mostrarMenuTurno(Jugador& jugador) {
    
    if (jugador.tieneUnaCarta() && !jugador.haDichoUNO()) {
        cout <<AMAR_BRILLANTE<< "!  ¡Tienes UNA carta y NO has cantado UNO!\n" <<RESET;
    }
}

void JuegoUNO::manejarCantoUNO(Jugador& jugador) {
    if (jugador.tieneDosCartas()) {
        jugador.cantarUNO();
        cout <<VERDE_BRILLANTE<< "GIRTAR:" << jugador.getNombre() << " grita: ¡UNO!\n" <<RESET;
    } else {
        cout <<BG_ROJO<< "X" <<RESET<< " No puedes cantar UNO si no tienes una sola carta.\n";
    }
}

void JuegoUNO::manejarAcusarUNO(Jugador& acusador) {
    cout << "\n¿A quién quieres acusar de no haber cantado UNO?\n";
    
    // Mostrar lista de otros jugadores
    int numJugadores = jugadores.size();
    for (int i = 0; i < numJugadores; i++) {
        const Jugador& j = jugadores.obtenerJugadorEnPosicion(i);
        if (j.getNombre() != acusador.getNombre()) {
            cout << "  [" << i << "] " << j.getNombre();
            if (j.tieneUnaCarta()) {
                cout << " (TIENE 1 CARTA)";
                if (!j.haDichoUNO()) {
                    cout << " - ¡NO DIJO UNO!";
                }
            }
            cout << "\n";
        }
    }
    
    cout << "Elige (o cualquier otra tecla para cancelar): ";
    string opcion;
    cin >> opcion;
    
    try {
        int indice = stoi(opcion);
        if (indice >= 0 && indice < numJugadores) {
            const Jugador& acusado = jugadores.obtenerJugadorEnPosicion(indice);
            
            if (acusado.getNombre() == acusador.getNombre()) {
                cout <<ROJO_BRILLANTE<< "X" <<RESET<< " No puedes acusarte a ti mismo.\n";
                return;
            }
            
            if (acusado.tieneUnaCarta() && !acusado.haDichoUNO()) {
                cout <<VERDE_BRILLANTE<< "¡Acusación válida! " << acusado.getNombre() 
                     << " no dijo UNO y roba 2 cartas.\n" <<RESET;
                
                // Dar castigo: robar 2 cartas
                Jugador& acusadoMod = const_cast<Jugador&>(acusado);
                for (int i = 0; i < 2; i++) {
                    if (!mazo.estaVacio()) {
                        acusadoMod.robarCarta(mazo);
                    }
                }
            } else {
                cout <<BG_ROJO<< "X" <<RESET<< " Acusación falsa. " << acusador.getNombre() 
                     << " roba 2 cartas por mentir.\n";
                
                // Acusador castigado
                for (int i = 0; i < 2; i++) {
                    if (!mazo.estaVacio()) {
                        const_cast<Jugador&>(acusador).robarCarta(mazo);
                    }
                }
            }
        }
    } catch (...) {
        cout << "Acusación cancelada.\n";
    }
}

void JuegoUNO::robarCarta() {
    Jugador& actual = jugadores.obtenerActual();
    
    if (mazo.estaVacio()) {
        cout <<ROJO_BRILLANTE<< "X" <<RESET<< " El mazo está vacío. No se puede robar.\n";
        return;
    }
    
    Carta* cartaRobada = mazo.desapilar();
    actual.getMano().agregarCarta(cartaRobada);
    
    cout << "ROBAR: " << actual.getNombre() << " roba: ";
    cartaRobada->mostrar();
    cout << "\n";
    
    // Verificar si la carta robada es jugable
    if (cartaRobada->esJugable(*cartaSuperior)) {
        cout <<BG_VERDE<< "¡La carta robada es jugable! ¿Quieres jugarla? (s/n): " <<RESET;
        char respuesta;
        cin >> respuesta;
        
        if (toupper(respuesta) == 'S') {
            // Buscar el índice de la carta recién robada
            for (int i = 0; i < actual.cartasEnMano(); i++) {
                Carta* carta = actual.getMano().obtenerCarta(i);
                // Comparación simple (necesitarías un método mejor)
                if (carta == cartaRobada) {
                    procesarJugada(i);
                    break;
                }
            }
        }
    }
}

bool JuegoUNO::procesarJugada(int indice) {
    Jugador& actual = jugadores.obtenerActual();
    Carta* cartaJugada = actual.jugarCarta(indice);
    
    if (cartaJugada == nullptr) {
        cout <<BG_ROJO<< "X" <<RESET<< " Error al obtener la carta.\n";
        return false;
    }
    
    if (cartaJugada->esJugable(*cartaSuperior)) {
        cout <<BG_VERDE<< " " << actual.getNombre() << " juega: " <<RESET;
        cartaJugada->mostrar();
        cout << "\n";
        
        // Liberar la carta superior anterior
        delete cartaSuperior;
        
        // Actualizar carta superior
        cartaSuperior = cartaJugada;
        
        // Ejecutar acción de la carta
        cartaSuperior->ejecutarAccion(*this);
        
        // Verificar UNO después de jugar
        if (actual.tieneUnaCarta()) {
            cout << "!  " << actual.getNombre() << " tiene UNA carta. ";
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
        cout <<BG_ROJO<< "X" <<RESET<< " Carta no válida. Debe coincidir color o número.\n";
        // Devolver la carta a la mano
        actual.getMano().agregarCarta(cartaJugada);
        return false;
    }
}

bool JuegoUNO::juegoTerminado() {
    return jugadores.obtenerActual().cartasEnMano() == 0;
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

void limpiarBuffer() {
    cin.clear(); // Limpiar flags de error
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar todo hasta el siguiente ENTER
}