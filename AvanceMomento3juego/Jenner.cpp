/*
#include "jenner.h"

Jenner::Jenner()
    : x(200), y(200), spriteX(0), spriteY(0),
    spriteAncho(60), spriteAlto(64), cont(0)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprite.load("./sprites_completos_2.png");
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    setPos(x, y);
}

void Jenner::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        movimiento(-5,0);
        confSprite(128);
        break;
    case Qt::Key_D:
        movimiento(5,0);
        confSprite(64);
        break;
    case Qt::Key_W:
        movimiento(0,-5);
        confSprite(192);
        break;
    case Qt::Key_S:
        movimiento(0,5);
        confSprite(0);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Jenner::movimiento(int dx, int dy)
{
    x += dx;
    y += dy;
    setPos(x, y);
}

void Jenner::confSprite(int dir)
{
    spriteY = dir;
    spriteX = spriteAncho * cont;
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    cont++;
    if (cont >= 2) cont = 0;
}

qreal Jenner::getX() const
{
    return x;
}
*/

#include "jenner.h"

Jenner::Jenner()
    : x(200), y(200), spriteX(0), spriteY(0),
    spriteAncho(60), spriteAlto(64), cont(0),
    vida(100), vidaMaxima(100), invulnerable(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprite.load("./sprites_completos_2.png");
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    setPos(x, y);
}

void Jenner::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        movimiento(-5,0);
        confSprite(128);
        break;
    case Qt::Key_D:
        movimiento(5,0);
        confSprite(64);
        break;
    case Qt::Key_W:
        movimiento(0,-5);
        confSprite(192);
        break;
    case Qt::Key_S:
        movimiento(0,5);
        confSprite(0);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Jenner::movimiento(int dx, int dy)
{
    x += dx;
    y += dy;
    setPos(x, y);
}

void Jenner::confSprite(int dir)
{
    spriteY = dir;
    spriteX = spriteAncho * cont;
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    cont++;
    if (cont >= 2) cont = 0;
}

qreal Jenner::getX() const
{
    return x;
}


int Jenner::getVida() const
{
    return vida;
}

void Jenner::recibirDanio(int cantidad)
{
    if (invulnerable || vida <= 0) return;

    vida -= cantidad;
    if (vida < 0) vida = 0;

    emit vidaCambiada(vida);

    if (vida <= 0) {
        emit murio();
    }
}

bool Jenner::estaVivo() const
{
    return vida > 0;
}

void Jenner::setInvulnerable(bool estado)
{
    invulnerable = estado;
}

bool Jenner::esInvulnerable() const
{
    return invulnerable;
}
