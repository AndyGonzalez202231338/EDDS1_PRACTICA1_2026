#ifndef COLORES_H
#define COLORES_H

#include <string>
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

#define violeta "\033[35m"
#define naranja "\033[38;5;208m"
#define rosado  "\033[38;5;213m"

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

class Colores {
public:
    // Métodos estáticos para imprimir con colores
    static void printfColor(const string& texto, const string& color);
    
    // Colores básicos
    static void printfRojo(const string& texto);
    static void printfVerde(const string& texto);
    static void printfAmarillo(const string& texto);
    static void printfAzul(const string& texto);
    static void printfMagenta(const string& texto);
    static void printfCyan(const string& texto);
    
    // Colores brillantes
    static void printfRojoBrillante(const string& texto);
    static void printfVerdeBrillante(const string& texto);
    static void printfAmarilloBrillante(const string& texto);
    static void printfAzulBrillante(const string& texto);
    static void printfMagentaBrillante(const string& texto);
    static void printfCyanBrillante(const string& texto);
    static void printfBlancoBrillante(const string& texto);
    
    // Fondos
    static void printfFondoRojo(const string& texto);
    static void printfFondoVerde(const string& texto);
    static void printfFondoAmarillo(const string& texto);
    static void printfFondoAzul(const string& texto);
    static void printfFondoMagenta(const string& texto);
    static void printfFondoCyan(const string& texto);
    static void printfFondoBlanco(const string& texto);
    
    // Combinado
    static void printfPersonalizado(const string& texto, const string& color, const string& fondo);
};

#endif