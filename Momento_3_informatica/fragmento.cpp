#include "fragmento.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>

Fragmento::Fragmento(int dir, qreal posX, qreal posY, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    direccion = dir;

    // Crear un pixmap con color sólido (rojo brillante)
    QPixmap pixmapFragmento(20, 20);
    pixmapFragmento.fill(Qt::red);  // Color rojo para que sea bien visible
    setPixmap(pixmapFragmento);
    setOffset(-10, -10); // centrar el sprite

    // Inicializar posición
    posicionX = posX;
    posicionY = posY;
    setPos(posicionX, posicionY);

    // Configurar movimiento parabólico
    velocidadX = direccion * 6;  // velocidad horizontal (positiva o negativa según dirección)
    velocidadY = -8;              // velocidad inicial hacia arriba (negativa = arriba)
    gravedad = 0.5;               // gravedad que hace caer el proyectil

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fragmento::mover);
    timer->start(20);
}

Fragmento::~Fragmento()
{
    if (timer) timer->stop();
}

void Fragmento::mover()
{
    // Actualizar velocidad vertical (gravedad)
    velocidadY += gravedad;

    // Actualizar posiciones
    posicionX += velocidadX;
    posicionY += velocidadY;

    // Aplicar nueva posición
    setPos(posicionX, posicionY);

    // Eliminar si sale de los límites del mundo
    if (posicionX < -200 || posicionX > 3500 || posicionY > 800) {
        if (scene()) scene()->removeItem(this);
        deleteLater();
    }
}
