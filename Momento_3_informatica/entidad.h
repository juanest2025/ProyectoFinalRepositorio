#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Entidad(QObject *parent = nullptr);

    virtual void mover() = 0;

protected:
    qreal velocidad;
    qreal x;
    qreal y;
};

#endif // ENTIDAD_H
