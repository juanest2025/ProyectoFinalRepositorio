#ifndef VIRUSLINEAL_H
#define VIRUSLINEAL_H

#include "entidad.h"

class VirusLineal : public Entidad
{
    Q_OBJECT

public:
    VirusLineal(qreal xI, qreal yI);

    void actualizar() override;
};

#endif // VIRUSLINEAL_H
