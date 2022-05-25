#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //test();
    gameTimer.start(1000);
    connect(&gameTimer, &QTimer::timeout, this, &MainWindow::dealGameTimer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealGameTimer()
{
    Mymap.actionInARoll();
}

void MainWindow::test()
{
    PeaShooter a1;
    BigMouth b1;
    NormalZombie a2, a3;
    Ballon b2;
    Mymap.addCreature(a1, "(1,3)");
    Mymap.addCreature(b2, "(1,5)");
    Mymap.addCreature(b1, "(2,3)");
    Mymap.addCreature(a2, "(2,5)");
    Mymap.addCreature(a3, "(2,5)");
}

void MainWindow::on_pushButton_clicked()
{

}
