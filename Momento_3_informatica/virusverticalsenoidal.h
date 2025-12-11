#ifndef VIRUSVERTICALSENOIDAL_H
#define VIRUSVERTICALSENOIDAL_H

#include "entidad.h"
#include <QTimer>

class VirusVerticalSenoidal : public Entidad
{
    Q_OBJECT
public:
    VirusVerticalSenoidal(int xo = 2200, int yo = 100, int limLeft = 0, int limRight = 2500);
    ~VirusVerticalSenoidal();

    void mover() override;
    void disparar();

private:
    QTimer *timer;
    QTimer *timerDisparo;
    double angulo;
    double amplitud;
    int direccionY;
    int limiteI;
    int limiteS;
};

#endif // VIRUSVERTICALSENOIDAL_H

