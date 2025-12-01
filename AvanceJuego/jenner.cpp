#include "jenner.h"
#include <QKeyEvent>

Jenner::Jenner() {
    x = 200;
    y = 200;

    setFlag(QGraphicsItem::ItemIsFocusable); // ← correcto
    hojaSprite.load("./sprites_completos_2.png");

    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
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
    if (x>595){
        x = 595;
    }
    x += dx;
    y += dy;
    setPos(x, y);

}

void Jenner::confSprite(int dir)
{
    spriteY = dir;
    spriteX = spriteAncho*cont;
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    cont ++;
    if (cont == 2){cont = 0;}

}
