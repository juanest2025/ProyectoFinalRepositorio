#ifndef VIRUSLINEAL_H
#define VIRUSLINEAL_H

#include "entidad.h"
#include <QTimer>

class VirusLineal : public Entidad
{
    Q_OBJECT
public:
    VirusLineal(int Xo = 1500, int Yo = 200, int limiteInferior = -100, int limiteSuperior = 2500);
    ~VirusLineal();

    void mover() override;
    void disparar();

private:
    QTimer *timer;
    QTimer *timerDisparo;
    int limite;
    int limiteAparicion;
    qreal inicialY;
};

#endif // VIRUSLINEAL_H
