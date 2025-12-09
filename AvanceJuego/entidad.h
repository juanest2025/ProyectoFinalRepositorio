#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QLineF>

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Entidad(QObject *parent = nullptr)
        : QObject(parent), velocidad(0), x(0), y(0), movimientoActivo(true) {}

    virtual ~Entidad() = default;
    virtual void mover() = 0;

    void activarMovimiento(bool activo) { movimientoActivo = activo; }

    // distancia a cualquier QGraphicsItem (seguro y genérico)
    qreal distanciaA(QGraphicsItem *otro) {
        if (!otro) return std::numeric_limits<qreal>::infinity();
        return QLineF(this->pos(), otro->pos()).length();
    }

protected:
    qreal velocidad;
    qreal x;
    qreal y;
    bool movimientoActivo;
};

#endif // ENTIDAD_H
