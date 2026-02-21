#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>
using namespace std;

class InputUtils {
public:
    static string leerOpcion();
    static void pausa();
    static void limpiarPantalla();
    static int obtenerEnteroValido(int min, int max);
    static char leerOpcionChar();
    static bool confirmar(const string& mensaje);
};

#endif