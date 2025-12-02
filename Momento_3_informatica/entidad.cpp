#include "entidad.h"

Entidad::Entidad(QObject *parent)
    : QObject(parent), velocidad(5), x(0), y(0)
{
}
