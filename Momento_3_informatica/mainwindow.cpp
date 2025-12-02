#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jenner.h"
#include "viruslineal.h"
#include "virussenoidal.h"

#include <QTimer>
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear escena
    scene = new QGraphicsScene(this);

    // Cargar fondo
    QPixmap fondo("./fondo.png");

    if (fondo.isNull()) {
        qDebug() << "ERROR: No se encuentra fondol.jpg";
    }

    //CONFIGURAR MUNDO LARGO (SCROLL)

    int altoVista = ui->graphicsView->height();
    int anchoMundo = 3000;  // Mundo de nivel 1 — largo horizontal

    // Rectángulo del mundo
    scene->setSceneRect(0, 0, anchoMundo, altoVista);

    // ESCALAR FONDO para cubrir TODO el nivel 1
    QPixmap fondoEscalado = fondo.scaled(
        anchoMundo,
        altoVista,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    scene->setBackgroundBrush(fondoEscalado);

    //CONFIGURACIÓN DEL VIEW
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

    //CREAR JENNER
    Jenner *jug1 = new Jenner;
    scene->addItem(jug1);
    jug1->setPos(200, 200);
    jug1->setFlag(QGraphicsItem::ItemIsFocusable);
    jug1->setFocus();

    //VIRUS
    VirusLineal *v1 = new VirusLineal;
    scene->addItem(v1);

    VirusSenoidal *v2 = new VirusSenoidal;
    scene->addItem(v2);

    // DAR FOCO DE NUEVO A JENNER
    jug1->setFocus();


    //CÁMARA SIGUIENDO A JENNER (scroll)
    QTimer *camTimer = new QTimer(this);
    connect(camTimer, &QTimer::timeout, this, [=](){
        ui->graphicsView->centerOn(jug1);
    });
    camTimer->start(16);  // ~60 FPS
}

MainWindow::~MainWindow()
{
    delete ui;
}


