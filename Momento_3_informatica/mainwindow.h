#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Entidad;
class Jenner;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsTextItem *mensajeInicial = nullptr;
    QGraphicsRectItem *mensajeInicialFondo = nullptr;
    bool juegoPausado = false;

private slots:
    void verificarColisiones();
    void actualizarVida(int vidaActual);
    void gameOver();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<Entidad*> grupo1;
    QList<Entidad*> grupo2;
    QList<Entidad*> grupo3;


    Jenner *jugador;
    QLabel *labelVida;
    QLabel *labelHospitales;
    int hospitalesVisitados = 0;
    QTimer *timerColisiones;
    QTimer *timerInvulnerabilidad;
};

#endif // MAINWINDOW_H
