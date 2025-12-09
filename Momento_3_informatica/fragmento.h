#ifndef FRAGMENTO_H
#define FRAGMENTO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Fragmento : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Fragmento(int dir, qreal posX, qreal posY, QObject *parent = nullptr);
    ~Fragmento();

private slots:
    void mover();

private:
    int direccion;        // -1 izquierda, +1 derecha
    QTimer *timer;

    // Variables para movimiento parabólico
    qreal velocidadX;
    qreal velocidadY;
    qreal gravedad;
    qreal posicionX;
    qreal posicionY;
};

#endif // FRAGMENTO_H
