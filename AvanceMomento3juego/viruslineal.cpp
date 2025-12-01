#include "viruslineal.h"

VirusLineal::VirusLineal(qreal xI, qreal yI)
    : Entidad(xI, yI)
{
    hojaSprite.load("./virus_lineal.png");
    spriteActual = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);
}

void VirusLineal::actualizar()
{
    x -= 3;  // movimiento recto hacia la izquierda
    setPos(x, y);
}
