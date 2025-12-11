#ifndef VIRUSSENOIDAL_H
#define VIRUSSENOIDAL_H

#include "entidad.h"
#include <QTimer>

class VirusSenoidal : public Entidad
{
    Q_OBJECT
public:
    VirusSenoidal(int xo = 1500, int yo = 300, int limI = 0, int limS = 2500);
    ~VirusSenoidal();

    void mover() override;
    void disparar();

private:
    QTimer *timer;
    QTimer *timerDisparo;
    double angulo;
    double amplitud;
    int limiteI;
    int limiteS;
    qreal yInicial;
};

#endif // VIRUSSENOIDAL_H
