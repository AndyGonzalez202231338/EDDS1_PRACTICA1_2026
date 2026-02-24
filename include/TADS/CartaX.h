#ifndef CARTA_X_H
#define CARTA_X_H

#include "Carta.h"
#include "JuegoUNO.h"
#include <cstdlib>

class CartaX : public Carta {
private:
    int colorElegido;
    
public:
    CartaX();
    ~CartaX();
    
    int getTipo() const override;
    int getValor() const override;
    int getColor() const override;
    void mostrar() const override;
    bool esJugable(const Carta& cartaSuperior) const override;
    void ejecutarAccion(class JuegoUNO& juego) override;
    bool mismoTipoYValor(const Carta& otra) const override;
    bool esComodin() const override { return true; }
};

#endif