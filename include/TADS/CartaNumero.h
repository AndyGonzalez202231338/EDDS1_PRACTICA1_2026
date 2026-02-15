#ifndef CARTA_NUMERO_H
#define CARTA_NUMERO_H

#include "Carta.h"

class CartaNumero : public Carta {
private:
    int numero;

public:
    CartaNumero(int color, int numero);
    virtual ~CartaNumero();

    virtual int getTipo() const override;
    virtual int getValor() const override;
    virtual void mostrar() const override;
    virtual void ejecutarAccion(class JuegoUNO& juego) override;

protected:
    virtual bool mismoTipoYValor(const Carta& otra) const override;
};

#endif