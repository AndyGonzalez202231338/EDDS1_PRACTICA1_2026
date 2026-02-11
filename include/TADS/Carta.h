#ifndef CARTA_H
#define CARTA_H

#define TIPO_NUMERO 0
#define TIPO_ACCION 1
#define TIPO_COMODIN 2

#define SKIP 10
#define REVERSE 11
#define MAS2 12
#define MAS4 13
#define CAMBIO_COLOR 14

class Carta {
private:
    int colorClaro;
    int tipoClaro;
    int valorClaro;

    int colorOscuro;
    int tipoOscuro;
    int valorOscuro;

    bool ladoOscuro;

public:
    Carta();
    
    Carta(int colorClaro, int tipoClaro, int valorClaro, int colorOscuro, int tipoOscuro, int valorOscuro);

    int getColor() const;
    int getTipo() const;
    int getValor() const;
    bool esLadoOscuro() const;

    void voltear();

    bool esJugable(const Carta& cartaSuperior) const;
};

#endif
