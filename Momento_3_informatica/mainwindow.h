#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void actualizarScroll();
    void actualizarFondo();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;

    // Scroll del nivel
    int scrollX = 0;
    QTimer *timerScroll;

    // Fondo en movimiento
    QPixmap fondo;
    QGraphicsPixmapItem *fondoItem1;
    QGraphicsPixmapItem *fondoItem2;
    QTimer *timerFondo;
};

#endif // MAINWINDOW_H
