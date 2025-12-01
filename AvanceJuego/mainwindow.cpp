#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jenner.h"
#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,600,600);
    ui->graphicsView->setScene(escena);
    Jenner *jug1 = new Jenner;
    escena->addItem(jug1);
    jug1->setPos(200, 200);
    jug1->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}
