#ifndef VIRUSLINEAL_H
#define VIRUSLINEAL_H

#include "entidad.h"
#include <QTimer>

class VirusLineal : public Entidad
{
    Q_OBJECT
public:
    explicit VirusLineal();
    void mover() override;

private:
    QTimer *timer;
};

#endif // VIRUSLINEAL_H
