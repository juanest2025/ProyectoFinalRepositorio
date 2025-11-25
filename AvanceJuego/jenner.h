#ifndef JENNER_H
#define JENNER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Jenner : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Jenner(int x, int y);

protected:
    void keyPressEvent(QKeyEvent *event) override;  // para mover a Jenner
};

#endif
