
#ifndef JENNER_H
#define JENNER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QKeyEvent>
class MainWindow;

class Jenner : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Jenner();
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void confSprite(int dir);
    qreal getX() const;

    // Sistema de vida
    int getVida() const;
    void recibirDanio(int cantidad);
    bool estaVivo() const;
    void setInvulnerable(bool estado);
    bool esInvulnerable() const;

signals:
    void vidaCambiada(int vidaActual);
    void murio();
    void pedirQuitarMensajeInicial();

private:
    qreal x;
    qreal y;
    int spriteX;
    int spriteY;
    int spriteAncho;
    int spriteAlto;
    QPixmap hojaSprite;
    QPixmap sprites;
    int cont;
    bool hospital1Visitado = false;
    bool hospital2Visitado = false;
    bool hospital3Visitado = false;

    bool caminoDesbloqueado = false;
    bool mensajeInicialMostrado = false;
    bool mensajeFabricaMostrado = false;

    // Variables de vida
    int vida;
    int vidaMaxima;
    bool invulnerable;  // Para evitar daño múltiple rápido
};

#endif // JENNER_H

