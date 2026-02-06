#ifndef CARTA_H
#define CARTA_H

class Carta{
    private:
        int color;
        int tipo;
        int valor;
        bool ladoOscuro;
    public:
        Carta();
        Carta(int color, int tipo, int valor, bool ladoOscuro);

        int getColor();
        int getTipo();
        int getValor();
        bool getLadoOscuro();

        bool esJugable(Carta* cartaSuperior);
};

#endif