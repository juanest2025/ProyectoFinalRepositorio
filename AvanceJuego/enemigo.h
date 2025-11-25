enemigo.h
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"

    class Enemigo : public Entidad {
public:
    int daño;
    QString tipoMovimiento;

    Enemigo(float px, float py, float vel)
        : Entidad(px, py, vel), daño(10) {}

    virtual void atacar() {}
};

#endif
