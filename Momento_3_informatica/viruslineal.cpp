#include "viruslineal.h"
#include <QPixmap>

VirusLineal::VirusLineal()
{
    setPixmap(QPixmap("./VirusLineal.png").scaled(70,70));

    x = 1500;
    y = 200;
    setPos(x, y);

    velocidad = 4;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VirusLineal::mover);
    timer->start(30);
}

void VirusLineal::mover()
{
    x -= velocidad;
    setPos(x, y);

    // Reaparece a la derecha cuando sale del mapa
    if (x < -100)
        x = 2500;
}
