#ifndef CARTA_FLIP_H
#define CARTA_FLIP_H

#include "Carta.h"

class CartaFlip : public Carta {
private:
    // Lado claro
    int colorClaro;
    int tipoClaro;
    int valorClaro;
    
    // Lado oscuro
    int colorOscuro;
    int tipoOscuro;
    int valorOscuro;
    
    bool ladoOscuro;

public:
    CartaFlip(int cClaro, int tClaro, int vClaro, int cOscuro, int tOscuro, int vOscuro);
    virtual ~CartaFlip();

    static JuegoUNO* juegoActual;
    static void setJuegoActual(JuegoUNO* juego) { juegoActual = juego; }

    virtual int getColor() const override;
    virtual int getTipo() const override;
    virtual int getValor() const override;
    virtual void mostrar() const override;
    virtual void voltear() override;
    virtual bool esLadoOscuro() const override;
    virtual void ejecutarAccion(class JuegoUNO& juego) override;
    virtual bool esJugable(const Carta& cartaSuperior) const override;

protected:
    virtual bool mismoTipoYValor(const Carta& otra) const override;
};

#endif