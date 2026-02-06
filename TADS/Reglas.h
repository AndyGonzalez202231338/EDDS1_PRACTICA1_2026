#ifndef REGLAS_H
#define REGLAS_H

class Reglas {
private: 
    bool acumulacion;
    bool retoMasCuatro;
    bool roboHastaPerder;
    bool gritoUno;
    bool ganarConNegra;
    bool modoFlip;
public:
    Reglas();
    bool isAcumulacionActiva();
    bool isRetoMasCuatroActivo();
    bool isRoboHastaPerderActivo();
    bool isGritoUnoActivo();
    bool isGanarConNegraActivo();
    bool isModoFlipActivo();

    void setAcumulacion(bool estado);
    void setRetoMasCuatro(bool estado);
    void setRoboHastaPerder(bool estado);
    void setGritoUno(bool estado);
    void setGanarConNegra(bool estado);
    void setModoFlip(bool estado);
};
#endif