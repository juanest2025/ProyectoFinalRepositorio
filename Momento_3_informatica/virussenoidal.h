#ifndef VIRUSSENOIDAL_H
#define VIRUSSENOIDAL_H

#include "entidad.h"
#include <QTimer>

class VirusSenoidal : public Entidad
{
    Q_OBJECT
public:
    explicit VirusSenoidal();
    void mover() override;

private:
    QTimer *timer;
    qreal tiempo;
    qreal yBase;
};

#endif // VIRUSSENOIDAL_H
