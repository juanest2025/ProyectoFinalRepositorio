#include "enemigo.h"

Enemigo::Enemigo(float px, float py, float vel)
    : Entidad(px, py, vel), daño(10) {}

void Enemigo::atacar() {
    // Por defecto no hace nada
}
