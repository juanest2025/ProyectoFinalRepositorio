#include "jenner.h"
#include <QKeyEvent>

Jenner::Jenner(int x, int y) {
    setPos(x, y);

    // Cargar sprite (cámbialo por el tuyo)
    setPixmap(QPixmap(":/sprites/jenner.png"));

    // Necesario para recibir el teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Jenner::keyPressEvent(QKeyEvent *event) {
    int paso = 10;  // velocidad de movimiento

    int nx = x();
    int ny = y();

    // Movimiento simple con flechas o WASD
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        ny -= paso;
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        ny += paso;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        nx -= paso;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        nx += paso;
        break;
    }

    // Limites básicos (ajústalos al tamaño de tu escena)
    if (nx >= 0 && nx <= 750) setX(nx);
    if (ny >= 0 && ny <= 550) setY(ny);
}
