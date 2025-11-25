#include "fragmento.h"

Fragmento::Fragmento(float px, float py, float ang)
    : Entidad(px, py, 7),
    angulo(ang),
    gravedad(0.3) {
    setPos(x, y);
}

void Fragmento::moverParabolico() {
    float rad = qDegreesToRadians(angulo);
    x += velocidad * qCos(rad);
    y -= velocidad * qSin(rad);
    y += gravedad;
    setPos(x, y);
}
