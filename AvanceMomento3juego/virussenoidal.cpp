#include "virussenoidal.h"
#include <QtMath>

VirusSenoidal::VirusSenoidal(qreal xI, qreal yI,
                             qreal A, qreal F)
    : Entidad(xI, yI),
      amplitud(A),
      frecuencia(F)
{
    yBase = y;  // posición original

    hojaSprite.load("./virus_senoidal.png");
    spriteActual = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);
}

void VirusSenoidal::actualizar()
{
    x -= 3;  
    y = yBase + amplitud * qSin(frecuencia * x);

    setPos(x, y);
}
