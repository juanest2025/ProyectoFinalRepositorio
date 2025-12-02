#ifndef JENNER_H
#define JENNER_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>

class Jenner : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x;
    qreal y;

    int spriteX = 0;
    int spriteY = 0;
    int spriteAncho = 60;
    int spriteAlto = 64;
    QPixmap hojaSprite;
    QPixmap sprites;
    int cont = 0;

public:
    Jenner();
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void confSprite(int dir);
};

#endif // JENNER_H
