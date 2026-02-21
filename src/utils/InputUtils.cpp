#include "../utils/InputUtils.h"
#include "../utils/Colores.h"
#include <iostream>
#include <limits>
#include <sstream>  
using namespace std;

string InputUtils::leerOpcion() {
    string opcion;
    getline(cin, opcion);
    return opcion;
}

void InputUtils::pausa() {
    cout << VERDE_BRILLANTE << "\nPresiona Enter para continuar..." << RESET;
    string dummy;
    getline(cin, dummy); // Usar getline en lugar de leerOpcion()
}

void InputUtils::limpiarPantalla() {
    system("clear");
}

int InputUtils::obtenerEnteroValido(int min, int max) {
    int valor;
    while (true) {
        cin >> valor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un número válido (" << min << "-" << max << "): ";
        } 
        else if (valor < min || valor > max) {
            cout << "Error: Número fuera de rango (" << min << "-" << max << "): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

char InputUtils::leerOpcionChar() {
    string opcion = leerOpcion();
    if (opcion.empty()) return '\0';
    return toupper(opcion[0]);
}

bool InputUtils::confirmar(const string& mensaje) {
    cout << mensaje << " (s/n): ";
    char r = leerOpcionChar();
    return (r == 'S');
}