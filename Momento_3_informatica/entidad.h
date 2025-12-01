#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    qreal x;
    qreal y;

    QPixmap hojaSprite;
    QPixmap spriteActual;

    int spriteX = 0;
    int spriteY = 0;
    int spriteAncho = 60;
    int spriteAlto = 64;

    QTimer *timerMovimiento;

public:
    Entidad(qreal xI, qreal yI, QObject *parent = nullptr);

    virtual void actualizar() = 0;  //método virtual herencia 
};

#endif // ENTIDAD_H
