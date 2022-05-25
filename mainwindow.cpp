#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //test();
    //gameTimer.start(1000);
    //connect(&gameTimer, &QTimer::timeout, this, &MainWindow::dealGameTimer);

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
    PeaShooter* a1 = new PeaShooter;
    BigMouth* b1 = new BigMouth;
    NormalZombie* a2, *a3;
    Ballon *b2;
    a2 = new NormalZombie;
    a3 = new NormalZombie;
    b2 = new Ballon;
    Mymap.addCreature(a1, "(3,3)");
    Mymap.addCreature(b2, "(1,7)");
    Mymap.addCreature(b1, "(3,5)");
    Mymap.addCreature(a2, "(1,8)");
    Mymap.addCreature(a3, "(1,8)");
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);

    //画背景图
    p.drawPixmap(rect(), QPixmap("../res/AllMap.png"));

}


















