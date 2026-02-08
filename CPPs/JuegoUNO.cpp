#include "../TADS/JuegoUNO.h"

JuegoUNO::JuegoUNO() {
    juegoActivo = false;
}

void JuegoUNO::configurarJuego() {
    // activar reglas desde menú
}

void JuegoUNO::iniciarJuego() {
    juegoActivo = true;
}

void JuegoUNO::ejecutarTurno() {
    // lógica principal del turno
}

void JuegoUNO::verificarGanador() {
    // verificar si algún jugador quedó sin cartas
}
