#include "Menu.h"
#include "../utils/Colores.h"
#include "../utils/InputUtils.h"
#include <iostream>
using namespace std;

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
    Reglas& reglas = juego.getReglas();
    
    while (true) {
        cout << AMARILLO << "\n--- CONFIGURACION DE REGLAS ---\n" << RESET;
        cout << "1. Acumulacion "; mostrarEstado(reglas.isAcumulacionActiva()); cout << endl;
        cout << "2. Reto +4 "; mostrarEstado(reglas.isRetoMas4Activo()); cout << endl;
        cout << "3. Robo hasta poder "; mostrarEstado(reglas.isRoboHastaPoderActivo()); cout << endl;
        cout << "4. Grito UNO "; mostrarEstado(reglas.isGritoUNOActivo()); cout << endl;
        cout << "5. Ganar con negra "; mostrarEstado(reglas.isGanarConNegraActivo()); cout << endl;
        cout << "6. Modo Flip "; mostrarEstado(reglas.isModoFlipActivo()); cout << endl;
        cout << CYAN << "\n0. Volver\n" << RESET;
        
        int opcion = InputUtils::obtenerEnteroValido(0, 6);
        
        switch (opcion) {
            case 1: reglas.setAcumulacion(!reglas.isAcumulacionActiva()); break;
            case 2: reglas.setRetoMas4(!reglas.isRetoMas4Activo()); break;
            case 3: reglas.setRoboHastaPoder(!reglas.isRoboHastaPoderActivo()); break;
            case 4: reglas.setGritoUNO(!reglas.isGritoUNOActivo()); break;
            case 5: reglas.setGanarConNegra(!reglas.isGanarConNegraActivo()); break;
            case 6: reglas.setModoFlip(!reglas.isModoFlipActivo()); break;
            case 0: return;
        }
    }
}

void Menu::menuJugadores() {
    while (true) {
        cout << AMARILLO << "\n--- JUGADORES ---\n" << RESET;
        juego.mostrarJugadores();
        
        cout << CYAN << "1. Agregar\n2. Eliminar\n3. Eliminar todos\n0. Volver\n" << RESET;
        int opcion = InputUtils::obtenerEnteroValido(0, 3);
        
        if (opcion == 0) return;
        
        if (opcion == 1) {
            cout << "Nombre: ";
            string nombre = InputUtils::leerOpcion();
            juego.agregarJugador(nombre);
        }
        else if (opcion == 2) {
            cout << "Nombre a eliminar: ";
            string nombre = InputUtils::leerOpcion();
            juego.eliminarJugador(nombre);
        }
        else if (opcion == 3) {
            juego.eliminarTodosJugadores();
            cout << ROJO << "Todos eliminados.\n" << RESET;
        }
    }
}

void Menu::iniciar() {
    InputUtils::limpiarPantalla();
    
    while (true) {
        mostrarMenuPrincipal();
        int opcion = InputUtils::obtenerEnteroValido(0, 3);
        
        switch (opcion) {
            case 1: menuConfiguracion(); break;
            case 2: menuJugadores(); break;
            case 3: juego.iniciarJuego(); break;
            case 0: return;
        }
        InputUtils::limpiarPantalla();
    }
}