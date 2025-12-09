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
    QPixmap fondo("./fondo.png");
    if (fondo.isNull()) qDebug() << "ERROR: No se encuentra fondo.png";

    int altoVista = ui->graphicsView->height();
    int anchoMundo = 3000;
    scene->setSceneRect(0, 0, anchoMundo, altoVista);

    QPixmap fondoEscalado = fondo.scaled(anchoMundo, altoVista, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(fondoEscalado);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

    // Crear jugador y marcar en global
    jugador = new Jenner;
    jugador2 = jugador;
    scene->addItem(jugador);
    jugador->setPos(200, 200);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();

    // Conectar señales de vida
    connect(jugador, &Jenner::vidaCambiada, this, &MainWindow::actualizarVida);
    connect(jugador, &Jenner::murio, this, &MainWindow::gameOver);

    // Crear label de vida
    labelVida = new QLabel(this);
    labelVida->setStyleSheet("QLabel { background-color: rgba(0, 0, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    QFont font = labelVida->font();
    font.setPointSize(14);
    font.setBold(true);
    labelVida->setFont(font);
    labelVida->setText(QString("❤️ VIDA: %1/100").arg(jugador->getVida()));
    labelVida->setGeometry(10, 10, 150, 40);
    labelVida->raise();

    // GRUPO 1
    grupo1 << new VirusLineal(400, 200, -100, 1000)
           << new VirusSenoidal(800, 250, -100, 1000);
    for (auto v : grupo1) scene->addItem(v);

    // GRUPO 2
    grupo2 << new VirusLineal(1200, 200, 1000, 2000)
           << new VirusSenoidal(1500, 300, 1000, 2000);
    for (auto v : grupo2) scene->addItem(v);

    // GRUPO 3
    grupo3 << new VirusVerticalSenoidal(2200, 200, 2000, 3000)
           << new VirusLineal(2600, 150, 2000, 3000);
    for (auto v : grupo3) scene->addItem(v);

    // Cámara
    QTimer *camTimer = new QTimer(this);
    connect(camTimer, &QTimer::timeout, this, [=](){
        ui->graphicsView->centerOn(jugador);
    });
    camTimer->start(16);

    // Control de activación por zonas
    QTimer *control = new QTimer(this);
    connect(control, &QTimer::timeout, this, [=](){
        qreal px = jugador->getX();
        bool g1_activo = (px >= 0 && px < 1000);
        for (auto v : grupo1) v->activarMovimiento(g1_activo);

        bool g2_activo = (px >= 1000 && px < 2000);
        for (auto v : grupo2) v->activarMovimiento(g2_activo);

        bool g3_activo = (px >= 2000 && px <= 3000);
        for (auto v : grupo3) v->activarMovimiento(g3_activo);
    });
    control->start(100);

    // Timer de detección de colisiones
    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
    timerColisiones->start(30); // Revisar colisiones cada 30ms

    // Timer para invulnerabilidad temporal
    timerInvulnerabilidad = new QTimer(this);
    timerInvulnerabilidad->setSingleShot(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verificarColisiones()
{
    if (!jugador->estaVivo()) return;

    // Obtener todos los items que colisionan con el jugador
    QList<QGraphicsItem*> itemsColisionados = jugador->collidingItems();

    for (QGraphicsItem *item : itemsColisionados) {
        // Verificar colisión con Fragmento
        Fragmento *fragmento = dynamic_cast<Fragmento*>(item);
        if (fragmento && !jugador->esInvulnerable()) {
            jugador->recibirDanio(5); // 5 puntos de daño por fragmento

            // Eliminar el fragmento
            scene->removeItem(fragmento);
            fragmento->deleteLater();

            // Activar invulnerabilidad temporal (500ms)
            jugador->setInvulnerable(true);
            timerInvulnerabilidad->start(500);
            connect(timerInvulnerabilidad, &QTimer::timeout, this, [=](){
                jugador->setInvulnerable(false);
            });

            // Efecto visual (opcional): hacer parpadear al jugador
            jugador->setOpacity(0.5);
            QTimer::singleShot(500, this, [=](){
                if (jugador) jugador->setOpacity(1.0);
            });

            qDebug() << "¡Jenner golpeado por fragmento! Vida:" << jugador->getVida();
            continue;
        }

        // Verificar colisión con Virus (Entidad)
        Entidad *virus = dynamic_cast<Entidad*>(item);
        if (virus && !jugador->esInvulnerable()) {
            jugador->recibirDanio(10); // 10 puntos de daño por contacto con virus

            // Activar invulnerabilidad temporal (1 segundo)
            jugador->setInvulnerable(true);
            timerInvulnerabilidad->start(1000);
            connect(timerInvulnerabilidad, &QTimer::timeout, this, [=](){
                jugador->setInvulnerable(false);
            });

            // Efecto visual
            jugador->setOpacity(0.3);
            QTimer::singleShot(1000, this, [=](){
                if (jugador) jugador->setOpacity(1.0);
            });

            qDebug() << "¡Jenner chocó con virus! Vida:" << jugador->getVida();
        }
    }
}

void MainWindow::actualizarVida(int vidaActual)
{
    labelVida->setText(QString("❤️ VIDA: %1/100").arg(vidaActual));

    // Cambiar color según vida
    if (vidaActual > 60) {
        labelVida->setStyleSheet("QLabel { background-color: rgba(0, 150, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    } else if (vidaActual > 30) {
        labelVida->setStyleSheet("QLabel { background-color: rgba(200, 150, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    } else {
        labelVida->setStyleSheet("QLabel { background-color: rgba(200, 0, 0, 150); color: white; padding: 10px; border-radius: 5px; }");
    }
}

void MainWindow::gameOver()
{
    // Detener todos los timers
    timerColisiones->stop();

    // Desactivar movimiento de todos los virus
    for (auto v : grupo1) v->activarMovimiento(false);
    for (auto v : grupo2) v->activarMovimiento(false);
    for (auto v : grupo3) v->activarMovimiento(false);

    // Mostrar mensaje de Game Over
    QMessageBox::critical(this, "GAME OVER", "¡Jenner ha muerto!\n\nVida: 0/100");

    qDebug() << "GAME OVER - Jenner ha muerto";
}

