#include "jenner.h"
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"

Jenner::Jenner()
    : x(200), y(200), spriteX(0), spriteY(0),
    spriteAncho(60), spriteAlto(64), cont(0),
    vida(100), vidaMaxima(100), invulnerable(false)
{

    hojaSprite.load("./sprites_completos_2.png");
    sprites = hojaSprite.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprites);
    setPos(x, y);

}


void Jenner::keyPressEvent(QKeyEvent *event)
{

    qreal oldX = x;
    qreal oldY = y;

    switch (event->key()) {

    case Qt::Key_A:
        movimiento(-5,0);
        confSprite(128);
        break;

    case Qt::Key_D:

        movimiento(5,0);

        // Requisito para avanzar
        if (!caminoDesbloqueado && x > 2000)
        {
            if (!mensajeFabricaMostrado)
            {
                QMessageBox::information(nullptr, "Bloqueado",
                                         "Aún no puedes avanzar.\n\n"
                                         "Debes visitar los 3 hospitales primero.");
                mensajeFabricaMostrado = true;
            }

            x = oldX;
            y = oldY;
            setPos(x, y);
            return;
        }

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
        return;
    }

    // Dectetar colisiones
    QList<QGraphicsItem*> col = collidingItems();

    for (QGraphicsItem *item : col)
    {
        QString tag = item->data(0).toString();

        // Aplicar física.
        if (tag == "hospital1")
        {
            hospital1Visitado = true;
            x = oldX;
            y = oldY;
            setPos(x, y);
        }
        if (tag == "hospital2")
        {
            hospital2Visitado = true;
            x = oldX;
            y = oldY;
            setPos(x, y);
        }
        if (tag == "hospital3")
        {
            hospital3Visitado = true;
            x = oldX;
            y = oldY;
            setPos(x, y);
        }

        //  Cuando toca los 3 hospitales
        if (hospital1Visitado && hospital2Visitado && hospital3Visitado)
            caminoDesbloqueado = true;

        // Requisito para ganar.
        if (tag == "fabrica" && caminoDesbloqueado)
        {
            QMessageBox::information(nullptr, "Victoria",
                                     "¡Has completado la misión!\nLlegaste a la fábrica.");
        }
    }
}


void Jenner::movimiento(int dx, int dy)
{
    qreal nuevaX = x + dx;
    qreal nuevaY = y + dy;

    qreal minX = 0;
    qreal maxX = 4000 - spriteAncho; //Ajusta posición para no salirse de la escena.
    qreal minY = 0;
    qreal maxY = 730 - spriteAlto;

    if (nuevaX < minX) nuevaX = minX;
    if (nuevaX > maxX) nuevaX = maxX;

    if (nuevaY < minY) nuevaY = minY;
    if (nuevaY > maxY) nuevaY = maxY;

    x = nuevaX;
    y = nuevaY;
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
