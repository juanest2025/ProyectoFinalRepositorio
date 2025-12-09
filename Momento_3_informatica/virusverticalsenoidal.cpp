#include "virusverticalsenoidal.h"
#include "fragmento.h"
#include "global.h"
#include "jenner.h"
#include <QPixmap>
#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsItem>

VirusVerticalSenoidal::VirusVerticalSenoidal(int xo, int yo, int limLeft, int limRight)
    : angulo(0), amplitud(20), direccionY(1), limiteI(limLeft), limiteS(limRight)
{
    setPixmap(QPixmap("./VirusSenoidal.png").scaled(70,70));
    x = xo;
    y = yo;
    setPos(x, y);

    velocidad = 2;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VirusVerticalSenoidal::mover);
    timer->start(30);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &VirusVerticalSenoidal::disparar);
    timerDisparo->start(1100);
}

VirusVerticalSenoidal::~VirusVerticalSenoidal()
{
    if (timer) timer->stop();
    if (timerDisparo) timerDisparo->stop();
}

void VirusVerticalSenoidal::mover()
{
    if (!movimientoActivo) return;

    y += direccionY * velocidad;

    if (y <= 0) direccionY = 1;
    if (y >= 600) direccionY = -1;

    x += qSin(angulo) * amplitud;
    angulo += 0.12;

    setPos(x, y);

    if (x < limiteI) x = limiteS;
}

void VirusVerticalSenoidal::disparar()
{
    if (!movimientoActivo) return;
    if (!jugador2) return;

    qreal d = distanciaA(static_cast<QGraphicsItem*>(jugador2));
    if (d > 200) return;  // Este virus dispara a menor distancia

    int direccion = (jugador2->pos().x() < pos().x()) ? -1 : 1;

    // Crear fragmento con trayectoria parabólica
    Fragmento *f = new Fragmento(direccion, pos().x(), pos().y() + 20, this);
    if (scene()) scene()->addItem(f);
}

