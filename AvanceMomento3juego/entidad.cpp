#include "entidad.h"

Entidad::Entidad(qreal xI, qreal yI, QObject *parent)
    : QObject(parent), x(xI), y(yI)
{
    // Timer para movimiento
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Entidad::actualizar);
    timerMovimiento->start(30); // 33 FPS aprox

    setPos(x, y);
}
