#include "virussenoidal.h"
#include <QPixmap>
#include <QtMath>

VirusSenoidal::VirusSenoidal()
{
    setPixmap(QPixmap("./VirusSenoidal.png").scaled(70,70));

    x = 1800;
    yBase = 250;
    y = yBase;

    tiempo = 0;

    setPos(x, y);

    velocidad = 3;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VirusSenoidal::mover);
    timer->start(30);
}

void VirusSenoidal::mover()
{
    x -= velocidad;

    tiempo += 0.15;
    y = yBase + qSin(tiempo) * 80;

    setPos(x, y);

    if (x < -100)
        x = 2600;
}
