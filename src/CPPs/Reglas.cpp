#include "Reglas.h"

Reglas::Reglas() {
    acumulacion = false;
    retoMas4 = false;
    roboHastaPoder = false;
    gritoUNO = false;
    ganarConNegra = false;
    modoFlip = false;
}

bool Reglas::isAcumulacionActiva() const { return acumulacion; }
bool Reglas::isRetoMas4Activo() const { return retoMas4; }
bool Reglas::isRoboHastaPoderActivo() const { return roboHastaPoder; }
bool Reglas::isGritoUNOActivo() const { return gritoUNO; }
bool Reglas::isGanarConNegraActivo() const { return ganarConNegra; }
bool Reglas::isModoFlipActivo() const { return modoFlip; }

void Reglas::setAcumulacion(bool estado) { acumulacion = estado; }
void Reglas::setRetoMas4(bool estado) { retoMas4 = estado; }
void Reglas::setRoboHastaPoder(bool estado) { roboHastaPoder = estado; }
void Reglas::setGritoUNO(bool estado) { gritoUNO = estado; }
void Reglas::setGanarConNegra(bool estado) { ganarConNegra = estado; }
void Reglas::setModoFlip(bool estado) { modoFlip = estado; }
