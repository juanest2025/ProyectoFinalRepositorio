#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>
#include "jenner.h"
#include "virusrectilineo.h"
#include "fragmento.h"

class Nivel1 {
public:
    QGraphicsScene* escena;
    QList<Enemigo*> listaVirus;
    Jenner* jenner;

    Nivel1(QGraphicsScene* s) : escena(s) {}

    void iniciar() {
        jenner = new Jenner(100, 200);
        escena->addItem(jenner);

        generarVirusRect();
    }

    void generarVirusRect() {
        auto v = new VirusRectilineo(700, 200);
        escena->addItem(v);
        listaVirus.append(v);
    }
};

#endif
