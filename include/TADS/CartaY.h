#ifndef CARTA_Y_H
#define CARTA_Y_H

#include "Carta.h"
#include "JuegoUNO.h"

class CartaY : public Carta {
private:
    int colorElegido;
    
public:
    CartaY();
    ~CartaY();
    
    int getTipo() const override;
    int getValor() const override; // Retorna 25
    int getColor() const override;
    void setColorElegido(int color);
    void mostrar() const override;
    bool esJugable(const Carta& cartaSuperior) const override;
    void ejecutarAccion(class JuegoUNO& juego) override;
    bool mismoTipoYValor(const Carta& otra) const override;
};

#endif