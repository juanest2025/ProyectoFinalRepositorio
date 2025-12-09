#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QLabel>
#include <QTimer>

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
    QTimer *timerColisiones;
    QTimer *timerInvulnerabilidad;
};

#endif // MAINWINDOW_H

