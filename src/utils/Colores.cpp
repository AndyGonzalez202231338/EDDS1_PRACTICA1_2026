#include "../utils/Colores.h"
#include <iostream>
using namespace std;


void Colores::printfColor(const string& texto, const string& color) {
    cout << color << texto << RESET;
}

void Colores::printfRojo(const string& texto) {
    cout << ROJO << texto << RESET;
}

void Colores::printfVerde(const string& texto) {
    cout << VERDE << texto << RESET;
}

void Colores::printfAmarillo(const string& texto) {
    cout << AMARILLO << texto << RESET;
}

void Colores::printfAzul(const string& texto) {
    cout << AZUL << texto << RESET;
}

void Colores::printfMagenta(const string& texto) {
    cout << MAGENTA << texto << RESET;
}

void Colores::printfCyan(const string& texto) {
    cout << CYAN << texto << RESET;
}

void Colores::printfRojoBrillante(const string& texto) {
    cout << ROJO_BRILLANTE << texto << RESET;
}

void Colores::printfVerdeBrillante(const string& texto) {
    cout << VERDE_BRILLANTE << texto << RESET;
}

void Colores::printfAmarilloBrillante(const string& texto) {
    cout << AMAR_BRILLANTE << texto << RESET;
}

void Colores::printfAzulBrillante(const string& texto) {
    cout << AZUL_BRILLANTE << texto << RESET;
}

void Colores::printfMagentaBrillante(const string& texto) {
    cout << MAGENTA_BRIL << texto << RESET;
}

void Colores::printfCyanBrillante(const string& texto) {
    cout << CYAN_BRILLANTE << texto << RESET;
}

void Colores::printfBlancoBrillante(const string& texto) {
    cout << BLANCO_BRIL << texto << RESET;
}

// Fondos
void Colores::printfFondoRojo(const string& texto) {
    cout << BG_ROJO << texto << RESET;
}

void Colores::printfFondoVerde(const string& texto) {
    cout << BG_VERDE << texto << RESET;
}

void Colores::printfFondoAmarillo(const string& texto) {
    cout << BG_AMARILLO << texto << RESET;
}

void Colores::printfFondoAzul(const string& texto) {
    cout << BG_AZUL << texto << RESET;
}

void Colores::printfFondoMagenta(const string& texto) {
    cout << BG_MAGENTA << texto << RESET;
}

void Colores::printfFondoCyan(const string& texto) {
    cout << BG_CYAN << texto << RESET;
}

void Colores::printfFondoBlanco(const string& texto) {
    cout << BG_BLANCO << texto << RESET;
}

// Versátil: permite combinar color y fondo
void Colores::printfPersonalizado(const string& texto, const string& color, const string& fondo) {
    cout << color << fondo << texto << RESET;
}