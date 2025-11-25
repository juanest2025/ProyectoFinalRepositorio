#include "nivel1.h"
#include "Jenner.h"

Nivel1::Nivel1(QGraphicsScene *s)
    : escena(s), jenner(nullptr) {}

void Nivel1::iniciar() {

    // Crear a Jenner (ya con el movimiento por teclado)
    jenner = new Jenner(100, 200);
    escena->addItem(jenner);

    // Muy importante: permitir que Jenner reciba teclado
    jenner->setFlag(QGraphicsItem::ItemIsFocusable);
    jenner->setFocus();

    generarVirusRect();
}

void Nivel1::generarVirusRect() {
    auto v = new VirusRectilineo(700, 200);
    escena->addItem(v);
    listaVirus.append(v);
}

