#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define CYAN    "\033[36m"

Menu::Menu() {}

void Menu::mostrarEstado(bool estado) {
    if (estado) {
        cout << VERDE << "[ACTIVADO]" << RESET;
    } else {
        cout << ROJO << "[DESACTIVADO]" << RESET;
    }
}

void Menu::mostrarMenuPrincipal() {
    cout << AMARILLO << "\n===== JUEGO UNO =====\n" << RESET;
    cout << "1. Configurar partida\n";
    cout << "2. Ingresar jugadores\n";
    cout << "3. Iniciar juego\n";
    cout << "0. Salir\n";
    cout << AMARILLO << "Seleccione una opcion: " << RESET;
}

void Menu::menuConfiguracion() {
    int opcion;
    bool salir = false;
    Reglas& reglas = juego.getReglas();

    while (!salir) {
        cout << AMARILLO << "\n--- CONFIGURACION DE REGLAS ---\n" << RESET;

        cout << "1. Acumulacion ";
        mostrarEstado(reglas.isAcumulacionActiva());
        cout << endl;

        cout << "2. Reto +4 ";
        mostrarEstado(reglas.isRetoMas4Activo());
        cout << endl;

        cout << "3. Modo Robo hasta poder jugar ";
        mostrarEstado(reglas.isRoboHastaPoderActivo());
        cout << endl;

        cout << "4. Grito UNO obligatorio ";
        mostrarEstado(reglas.isGritoUNOActivo());
        cout << endl;

        cout << "5. Ganar con carta negra ";
        mostrarEstado(reglas.isGanarConNegraActivo());
        cout << endl;

        cout << "6. Modo Flip ";
        mostrarEstado(reglas.isModoFlipActivo());
        cout << endl;

        cout << CYAN << "\n0. Volver\n" << RESET;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                reglas.setAcumulacion(!reglas.isAcumulacionActiva());
                break;
            case 2:
                reglas.setRetoMas4(!reglas.isRetoMas4Activo());
                break;
            case 3:
                reglas.setRoboHastaPoder(!reglas.isRoboHastaPoderActivo());
                break;
            case 4:
                reglas.setGritoUNO(!reglas.isGritoUNOActivo());
                break;
            case 5:
                reglas.setGanarConNegra(!reglas.isGanarConNegraActivo());
                break;
            case 6:
                reglas.setModoFlip(!reglas.isModoFlipActivo());
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << ROJO << "Opcion invalida\n" << RESET;
        }
    }
}

void Menu::menuJugadores() {
    int opcion;
    bool salir = false;
    string nombre;

    while (!salir) {
        cout << AMARILLO << "\n--- JUGADORES REGISTRADOS ---\n" << RESET;
        juego.mostrarJugadores();

        do {
            cout << CYAN << "\n1. Agregar jugador\n";
            cout << "2. Eliminar jugador\n";
            cout << "3. Eliminar todos\n";
            cout << "0. Volver\n" << RESET;
            cout << "Opcion: ";
            
            opcion = obtenerEnteroValido(0, 3);
            
        } while (opcion < 0 || opcion > 3); 
        switch (opcion) {
            case 1:
                cout << "Nombre del jugador: ";
                cin >> nombre;
                juego.agregarJugador(nombre);
                break;

            case 2:
                cout << "Nombre del jugador a eliminar: ";
                cin >> nombre;
                juego.eliminarJugador(nombre);
                break;

            case 3:
                juego.eliminarTodosJugadores();
                cout << ROJO << "Todos los jugadores eliminados.\n" << RESET;
                break;

            case 0:
                salir = true;
                break;

            default:
                cout << ROJO << "Opcion invalida\n" << RESET;
        }
    }
}


void Menu::iniciar() {
    int opcion;
    bool salir = false;

    while (!salir) {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuConfiguracion();
                break;
            case 2:
                menuJugadores();
                break;
            case 3:

                juego.iniciarJuego();
                mostrarTurnoActual();
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida\n";
        }
    }
}

int Menu::obtenerEnteroValido(int min, int max) {
    int valor;
    while (true) {
        cin >> valor;
        
        if (cin.fail()) {
            // Limpiar error de cin
            cin.clear();
            // Descartar entrada inválida
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un número válido (" << min << "-" << max << "): ";
        } 
        else if (valor < min || valor > max) {
            cout << "Error: Número fuera de rango (" << min << "-" << max << "): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            // Limpiar buffer si queda algo
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

void Menu::mostrarTurnoActual() {
    cout << AMARILLO << "\nTURNO ACTUAL\n" << RESET;
    cout << VERDE << juego.obtenerActual().getNombre() << RESET << endl;
}

