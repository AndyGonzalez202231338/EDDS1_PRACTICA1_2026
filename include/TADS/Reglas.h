#ifndef REGLAS_H
#define REGLAS_H

class Reglas {
private:
    bool acumulacion;
    bool retoMas4;
    bool roboHastaPoder;
    bool gritoUNO;
    bool ganarConNegra;
    bool modoFlip;

public:
    Reglas();

    bool isAcumulacionActiva() const;
    bool isRetoMas4Activo() const;
    bool isRoboHastaPoderActivo() const;
    bool isGritoUNOActivo() const;
    bool isGanarConNegraActivo() const;
    bool isModoFlipActivo() const;

    void setAcumulacion(bool estado);
    void setRetoMas4(bool estado);
    void setRoboHastaPoder(bool estado);
    void setGritoUNO(bool estado);
    void setGanarConNegra(bool estado);
    void setModoFlip(bool estado);
};

#endif
