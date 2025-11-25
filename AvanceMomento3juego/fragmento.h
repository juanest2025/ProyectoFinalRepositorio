#ifndef FRAGMENTO_H
#define FRAGMENTO_H

#include "entidad.h"
#include <qmath.h>

class Fragmento : public Entidad {
public:
    float angulo;  // en grados
    float gravedad;

    Fragmento(float px, float py, float ang)
        : Entidad(px, py, 7), angulo(ang), gravedad(0.3) {}

    void moverParabolico() {
        float rad = qDegreesToRadians(angulo);
        x += velocidad * qCos(rad);
        y -= velocidad * qSin(rad);
        y += gravedad;

        setPos(x, y);
    }
};

#endif
