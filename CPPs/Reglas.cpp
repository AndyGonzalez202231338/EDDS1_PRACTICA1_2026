#include "../TADS/Reglas.h"

Reglas::Reglas() {
    acumulacion = false;
    retoMasCuatro = false;
    roboHastaPerder = false;
    gritoUno = false;
    ganarConNegra = false;
    modoFlip = false;
}

bool Reglas::isAcumulacionActiva() {
    return acumulacion;
}

bool Reglas::isRetoMasCuatroActivo() {
    return retoMasCuatro;
}

bool Reglas::isRoboHastaPerderActivo() {
    return roboHastaPerder;
}

bool Reglas::isGritoUnoActivo() {
    return gritoUno;
}

bool Reglas::isGanarConNegraActivo() {
    return ganarConNegra;
}

bool Reglas::isModoFlipActivo() {
    return modoFlip;
}

void Reglas::setAcumulacion(bool estado) {
    acumulacion = estado;
}

void Reglas::setRetoMasCuatro(bool estado) {
    retoMasCuatro = estado;
}

void Reglas::setRoboHastaPerder(bool estado) {
    roboHastaPerder = estado;
}

void Reglas::setGritoUno(bool estado) {
    gritoUno = estado;
}

void Reglas::setGanarConNegra(bool estado) {
    ganarConNegra = estado;
}

void Reglas::setModoFlip(bool estado) {
    modoFlip = estado;
}
