#ifndef VIRUSSENOIDAL_H
#define VIRUSSENOIDAL_H

#include "entidad.h"

class VirusSenoidal : public Entidad
{
    Q_OBJECT

private:
    qreal amplitud;
    qreal frecuencia;
    qreal yBase;

public:
    VirusSenoidal(qreal xI, qreal yI,
                  qreal A = 40,
                  qreal F = 0.05);

    void actualizar() override;
};

#endif // VIRUSSENOIDAL_H
