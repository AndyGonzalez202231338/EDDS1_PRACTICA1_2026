#ifndef CARTA_FLIP_SPECIAL_H
#define CARTA_FLIP_SPECIAL_H

#include "Carta.h"
#include "JuegoUNO.h"

class CartaFlipSpecial : public Carta {
private:
    bool ladoOscuro;
    
public:
    static JuegoUNO* juegoActual; 
    
    CartaFlipSpecial();
    ~CartaFlipSpecial();
    
    static void setJuegoActual(JuegoUNO* juego) { juegoActual = juego; }
    
    int getTipo() const override;
    int getValor() const override;
    void mostrar() const override;
    bool esJugable(const Carta& cartaSuperior) const override;
    void ejecutarAccion(class JuegoUNO& juego) override;
    bool mismoTipoYValor(const Carta& otra) const override;
    void voltear() override;
    bool esLadoOscuro() const override;
};

#endif