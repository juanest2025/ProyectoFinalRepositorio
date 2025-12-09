#include "viruslineal.h"
#include "fragmento.h"
#include "global.h"
#include "jenner.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>

VirusLineal::VirusLineal(int Xo, int Yo, int limiteInferior, int limiteSuperior)
{
    setPixmap(QPixmap("./VirusLineal.png").scaled(70,70));
    limite = limiteInferior;
    limiteAparicion = limiteSuperior;
    x = Xo;
    y = Yo;
    inicialY = Yo;
    velocidad = 5;

    setPos(x, y);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VirusLineal::mover);
    timer->start(30);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &VirusLineal::disparar);
    timerDisparo->start(900); // comprobar cada 900 ms
}

VirusLineal::~VirusLineal()
{
    if (timer) timer->stop();
    if (timerDisparo) timerDisparo->stop();
}

void VirusLineal::mover()
{
    if (!movimientoActivo) return;

    x -= velocidad;

    if (x < limite) {
        x = limiteAparicion;
        y = inicialY;
    }

    setPos(x, y);
}

void VirusLineal::disparar()
{
    if (!movimientoActivo) return;
    if (!jugador2) return;

    qreal d = distanciaA(static_cast<QGraphicsItem*>(jugador2));
    if (d > 300) return;

    int direccion = (jugador2->pos().x() < pos().x()) ? -1 : 1;

    // Fragmento central
    Fragmento *f1 = new Fragmento(direccion, pos().x(), pos().y() + 20, this);

    // Fragmento superior (sale más arriba)
    Fragmento *f2 = new Fragmento(direccion, pos().x(), pos().y() + 10, this);

    // Fragmento inferior (sale más abajo)
    Fragmento *f3 = new Fragmento(direccion, pos().x(), pos().y() + 5, this);

    scene()->addItem(f1);
    scene()->addItem(f2);
    scene()->addItem(f3);
}
