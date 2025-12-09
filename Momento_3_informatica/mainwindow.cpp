#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jenner.h"
#include "viruslineal.h"
#include "virussenoidal.h"
#include "virusverticalsenoidal.h"
#include "fragmento.h"
#include "global.h"
#include <QTimer>
#include <QGraphicsView>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    // fondo del nivel
    QPixmap fondo("./fondo.png");
    if (fondo.isNull()) qDebug() << "ERROR: No se encuentra fondo.png";

    int altoVista = ui->graphicsView->height();

    int anchoMundo = 4000;

    scene->setSceneRect(0, 0, anchoMundo, altoVista);

    QPixmap fondoEscalado = fondo.scaled(anchoMundo, altoVista, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(fondoEscalado);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

    // jugador (jenner)
    jugador = new Jenner;
    jugador2 = jugador;  // global

    scene->addItem(jugador);
    jugador->setPos(200, 200);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();

    connect(jugador, &Jenner::vidaCambiada, this, &MainWindow::actualizarVida);
    connect(jugador, &Jenner::murio, this, &MainWindow::gameOver);

    // hud de vida
    labelVida = new QLabel(this);
    labelVida->setStyleSheet("QLabel { background-color: rgba(0, 0, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    QFont font = labelVida->font();
    font.setPointSize(14);
    font.setBold(true);
    labelVida->setFont(font);
    labelVida->setText(QString("❤️ VIDA: %1/100").arg(jugador->getVida()));
    labelVida->setGeometry(10, 10, 150, 40);
    labelVida->raise();

    // grupo 1 de virus
    grupo1 << new VirusLineal(500, 10,    0, 1000)
           << new VirusLineal(700, 50,    0, 1000)
           << new VirusLineal(900, 80,    0, 1000)
           << new VirusLineal(1100, 100,    0, 1000)
           << new VirusLineal(1300, 160,   0, 1000)
           << new VirusLineal(1550, 290,   0, 1000)
           << new VirusLineal(1570, 310,   0, 1000)
           << new VirusLineal(1690, 330,   0, 1000)
           << new VirusLineal(1710, 370,   0, 1000);
    for (auto v : grupo1) scene->addItem(v);


    // grupo 2 de virus
    grupo2 << new VirusSenoidal(1400, 200, 1300, 2300)
           << new VirusSenoidal(1600, 250, 1300, 2300)
           << new VirusSenoidal(1800, 150, 1300, 2300)
           << new VirusSenoidal(2000, 300, 1300, 2300)
           << new VirusSenoidal(2300, 220, 1300, 2300)
           << new VirusSenoidal(2500, 270, 1300, 2300)
           << new VirusSenoidal(2700, 240, 1300, 2300)
           << new VirusSenoidal(2900, 290, 1300, 2300)
           << new VirusSenoidal(3000, 320, 1300, 2300);
    for (auto v : grupo2) scene->addItem(v);

    // grupo 3 de virus
    grupo3 << new VirusVerticalSenoidal(2800, 200, 2300, 4000)
           << new VirusVerticalSenoidal(3000, 250, 2300, 4000)
           << new VirusVerticalSenoidal(3300, 150, 2300, 4000)
           << new VirusSenoidal(2800, 200, 2300, 5000)
           << new VirusSenoidal(3000, 250, 2300, 5000)
           << new VirusSenoidal(3300, 150, 2300, 5000)
           << new VirusLineal(3500, 180, 2300, 5000)
           << new VirusLineal(3700, 120, 2300, 5000);
    for (auto v : grupo3) scene->addItem(v);

    // hospital 1
    QGraphicsPixmapItem *hospital1 = new QGraphicsPixmapItem();
    QPixmap h1("hospital.png");

    if (h1.isNull()) {
        qDebug() << "ERROR: NO SE ENCUENTRA hospital.png";
    }

    h1 = h1.scaled(150, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    hospital1->setPixmap(h1);
    hospital1->setPos(1200, 90); // dentro sección 2

    scene->addItem(hospital1);

    // hospital 2
    QGraphicsPixmapItem *hospital2 = new QGraphicsPixmapItem();
    QPixmap h2("hospital.png");

    if (h2.isNull()) {
        qDebug() << "ERROR: NO SE ENCUENTRA hospital.png";
    }

    h2 = h2.scaled(150, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    hospital2->setPixmap(h2);
    hospital2->setPos(1600, 300); // posición distinta

    scene->addItem(hospital2);

    // hospital 3
    QGraphicsPixmapItem *hospital3 = new QGraphicsPixmapItem();
    QPixmap h3("hospital.png");

    h3 = h3.scaled(150, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    hospital3->setPixmap(h3);
    hospital3->setPos(2000, 500); // otro lugar

    scene->addItem(hospital3);

    // la fábrica
    QGraphicsPixmapItem *factory = new QGraphicsPixmapItem();

    QPixmap pixF("factory.png");

    // verificar carga
    qDebug() << "Cargando factory.png...";
    qDebug() << "factory cargado? ->" << !pixF.isNull();

    if (pixF.isNull()) {
        qDebug() << "ERROR: NO SE ENCUENTRA factory.png";
    }

    pixF = pixF.scaled(400, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    factory->setPixmap(pixF);
    factory->setPos(3000, 300);   // ← posición segura

    scene->addItem(factory);

    // cámara que sigue a jenner
    QTimer *camTimer = new QTimer(this);
    connect(camTimer, &QTimer::timeout, this, [=](){
        ui->graphicsView->centerOn(jugador);
    });
    camTimer->start(16);

    // activación por zonas
    QTimer *control = new QTimer(this);
    connect(control, &QTimer::timeout, this, [=](){
        qreal px = jugador->getX();

        bool g1_activo = (px >= 0 && px < 1300);
        for (auto v : grupo1) v->activarMovimiento(g1_activo);

        bool g2_activo = (px >= 1300 && px < 2600);
        for (auto v : grupo2) v->activarMovimiento(g2_activo);

        bool g3_activo = (px >= 2300 && px <= 5000);
        for (auto v : grupo3) v->activarMovimiento(g3_activo);
    });
    control->start(100);

    // colisiones
    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
    timerColisiones->start(30);

    timerInvulnerabilidad = new QTimer(this);
    timerInvulnerabilidad->setSingleShot(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// colisiones
void MainWindow::verificarColisiones()
{
    if (!jugador->estaVivo()) return;

    QList<QGraphicsItem*> itemsColisionados = jugador->collidingItems();

    for (QGraphicsItem *item : itemsColisionados) {

        // Daño por fragmento
        Fragmento *fragmento = dynamic_cast<Fragmento*>(item);
        if (fragmento && !jugador->esInvulnerable()) {

            jugador->recibirDanio(5);

            scene->removeItem(fragmento);
            fragmento->deleteLater();

            jugador->setInvulnerable(true);
            timerInvulnerabilidad->start(500);
            connect(timerInvulnerabilidad, &QTimer::timeout, this, [=](){
                jugador->setInvulnerable(false);
            });

            jugador->setOpacity(0.5);
            QTimer::singleShot(500, this, [=](){
                if (jugador) jugador->setOpacity(1.0);
            });

            continue;
        }

        // Daño por virus
        Entidad *virus = dynamic_cast<Entidad*>(item);
        if (virus && !jugador->esInvulnerable()) {

            jugador->recibirDanio(10);

            jugador->setInvulnerable(true);
            timerInvulnerabilidad->start(1000);
            connect(timerInvulnerabilidad, &QTimer::timeout, this, [=](){
                jugador->setInvulnerable(false);
            });

            jugador->setOpacity(0.3);
            QTimer::singleShot(1000, this, [=](){
                if (jugador) jugador->setOpacity(1.0);
            });
        }
    }
}

// actualizar hud
void MainWindow::actualizarVida(int vidaActual)
{
    labelVida->setText(QString("❤️ VIDA: %1/100").arg(vidaActual));

    if (vidaActual > 60) {
        labelVida->setStyleSheet("QLabel { background-color: rgba(0, 150, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    } else if (vidaActual > 30) {
        labelVida->setStyleSheet("QLabel { background-color: rgba(200, 150, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    } else {
        labelVida->setStyleSheet("QLabel { background-color: rgba(200, 0, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    }
}

// game over
void MainWindow::gameOver()
{
    timerColisiones->stop();

    for (auto v : grupo1) v->activarMovimiento(false);
    for (auto v : grupo2) v->activarMovimiento(false);
    for (auto v : grupo3) v->activarMovimiento(false);

    QMessageBox::critical(this, "GAME OVER", "¡Jenner ha muerto!\n\nVida: 0/100");
}


