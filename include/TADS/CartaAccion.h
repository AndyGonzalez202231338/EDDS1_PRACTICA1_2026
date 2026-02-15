#ifndef CARTA_ACCION_H
#define CARTA_ACCION_H

#include "Carta.h"

class CartaAccion : public Carta {
private:
    int tipoAccion; // SKIP(10), REVERSE(11), +2(12)

public:
    CartaAccion(int color, int tipoAccion);
    virtual ~CartaAccion();

    virtual int getTipo() const override;
    virtual int getValor() const override;
    virtual void mostrar() const override;
    virtual void ejecutarAccion(class JuegoUNO& juego) override;

protected:
    virtual bool mismoTipoYValor(const Carta& otra) const override;
};

#endif