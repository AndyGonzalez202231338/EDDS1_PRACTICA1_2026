#ifndef CARTA_COMODIN_H
#define CARTA_COMODIN_H

#include "Carta.h"

class CartaComodin : public Carta {
private:
    int tipoComodin; // +4(13), CAMBIO COLOR(14)
    int colorElegido;

public:
    CartaComodin(int tipoComodin, bool esOscuro = false);
    virtual ~CartaComodin();

    virtual int getTipo() const override;
    virtual int getValor() const override;
    virtual int getColor() const override;
    virtual void mostrar() const override;
    virtual bool esJugable(const Carta& cartaSuperior) const override;
    virtual void ejecutarAccion(class JuegoUNO& juego) override;

    void setColorElegido(int color);
    bool esMas4() const { return tipoComodin == 13; }
    bool tieneColorElegido() const { return colorElegido != -1; }
protected:
    virtual bool mismoTipoYValor(const Carta& otra) const override;
    virtual bool esComodin() const override;
};

#endif