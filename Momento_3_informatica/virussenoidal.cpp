#include "virussenoidal.h"
#include "fragmento.h"
#include "global.h"
#include "jenner.h"
#include <QPixmap>
#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsItem>

VirusSenoidal::VirusSenoidal(int xo, int yo, int limI, int limS)
    : angulo(0), amplitud(30), limiteI(limI), limiteS(limS)
{
    setPixmap(QPixmap("./VirusSenoidal.png").scaled(70,70));
    x = xo;
    y = yo;
    yInicial = yo;
    setPos(x, y);

    velocidad = 2;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VirusSenoidal::mover);
    timer->start(30);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &VirusSenoidal::disparar);
    timerDisparo->start(1200);
}

VirusSenoidal::~VirusSenoidal()
{
    if (timer) timer->stop();
    if (timerDisparo) timerDisparo->stop();
}

void VirusSenoidal::mover()
{
    if (!movimientoActivo) return;

    x -= velocidad;
    y = yInicial + qSin(angulo) * amplitud;
    angulo += 0.15;

    if (x < limiteI) {
        x = limiteS;
        y = yInicial;
    }
    setPos(x, y);
}


void VirusSenoidal::disparar()
{
    if (!movimientoActivo) return;
    if (!jugador2) return;

    qreal d = distanciaA(static_cast<QGraphicsItem*>(jugador2));
    if (d > 200) return;  // Solo dispara si está a menos de 300 unidades

    int direccion = (jugador2->pos().x() < pos().x()) ? -1 : 1;

    // Crear fragmento con trayectoria parabólica
    Fragmento *f = new Fragmento(direccion, pos().x(), pos().y() + 20, this);
    if (scene()) scene()->addItem(f);
}

