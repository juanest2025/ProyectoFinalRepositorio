#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jenner.h"
#include "viruslineal.h"
#include "virussenoidal.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear escena larga
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 4000, 600);   // nivel largo
    ui->graphicsView->setScene(escena);

    // Desactivar barras
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(800, 600);

    //fondo del juego 
    fondo.load(":/fondo_nivel1.png");  // usa el que tengas
    fondo = fondo.scaled(800, 600);

    fondoItem1 = escena->addPixmap(fondo);
    fondoItem2 = escena->addPixmap(fondo);

    fondoItem1->setPos(0, 0);
    fondoItem2->setPos(800, 0);

    // Timer fondo
    timerFondo = new QTimer(this);
    connect(timerFondo, &QTimer::timeout, this, &MainWindow::actualizarFondo);
    timerFondo->start(20);

    //jenner 
    Jenner *jenner = new Jenner();
    escena->addItem(jenner);
    jenner->setPos(200, 300);
    jenner->setFocus();

    //virus
    escena->addItem(new VirusLineal(1200, 250));
    escena->addItem(new VirusSenoidal(1800, 350));
    escena->addItem(new VirusSenoidal(2500, 300));
    escena->addItem(new VirusLineal(3200, 280));

    //scroll automático 
    timerScroll = new QTimer(this);
    connect(timerScroll, &QTimer::timeout, this, &MainWindow::actualizarScroll);
    timerScroll->start(16);  // ~60 FPS
}

MainWindow::~MainWindow()
{
    delete ui;
}

// scroll del nivel
void MainWindow::actualizarScroll()
{
    scrollX += 3;  // velocidad del nivel

    // Mover cámara (graphicsView) dentro de la escena
    ui->graphicsView->centerOn(scrollX, 300);

    // Limitar para que no cruce el final del nivel
    if (scrollX > 4000 - 400)
        scrollX = 4000 - 400;
}

//fondo que se repite
void MainWindow::actualizarFondo()
{
    // mover ambos fondos hacia la izquierda
    fondoItem1->setX(fondoItem1->x() - 2);
    fondoItem2->setX(fondoItem2->x() - 2);

    // Reiniciar cuando un fondo sale completo
    if (fondoItem1->x() <= -800)
        fondoItem1->setX(fondoItem2->x() + 800);

    if (fondoItem2->x() <= -800)
        fondoItem2->setX(fondoItem1->x() + 800);
}
