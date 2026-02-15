#ifndef MANO_H
#define MANO_H

#include "NodoCarta.h"

class Mano {
private:
    NodoCarta* cabeza;
    int cantidad;
public:
    Mano();
    ~Mano();

    void agregarCarta(Carta* carta);  
    Carta* eliminarCarta(int indice); 
    Carta* obtenerCarta(int indice) const; 
    void ordenar() const;
    void mostrar() const;

    bool tieneCartaJugable(const Carta& cartaSuperior) const;
    int contarCartas() const;
    
    void vaciar(); 
};

#endif