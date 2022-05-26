#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    sw.show();
    ui->setupUi(this);
    setFixedSize(P_LEN*8, P_LEN*5);

    peaButton = new QPushButton(this);
    bigmButton = new QPushButton(this);
    wallButton= new QPushButton(this);
    peaButton->setFixedSize(P_LEN/2,P_LEN/2);
    bigmButton->setFixedSize(P_LEN/2,P_LEN/2);
    wallButton->setFixedSize(P_LEN/2,P_LEN/2);
    peaButton->setIcon(QIcon(QPixmap(":/picture/res/PeaShooter.png")));
    bigmButton->setIcon(QIcon(QPixmap(":/picture/res/MeleePlant.png")));
    wallButton->setIcon(QIcon(QPixmap(":/picture/res/Wallnut0.png")));
    peaButton->hide();
    bigmButton->hide();
    wallButton->hide();


    //链接信号和槽
    connect(&gameTimer, &QTimer::timeout, this, &MainWindow::dealGameTimer);
    connect(&sw, &StartWidget::startGame, this, &MainWindow::startGame);
    connect(peaButton, &QPushButton::clicked, this, &MainWindow::addPeaShooter);
    connect(bigmButton, &QPushButton::clicked, this, &MainWindow::addBigMouth);
    connect(wallButton, &QPushButton::clicked, this, &MainWindow::addWallNut);

}

void MainWindow::startGame() {
    show();
    sw.hide();
    //测试函数
    //test();
    gameTimer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealGameTimer()
{
    Mymap.actionInARoll();
    if (Mymap.getGameover()) {
        gameTimer.stop();
        QMessageBox::about(this, "YOU LOSS", "Game Over!");
        hide();
        sw.show();
    }
    update();
}

void MainWindow::test()
{

}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);
    //qDebug() << "SB";
    //画背景图
    //p.drawPixmap(0, 0, 200, 200, QPixmap(":/picture/res/OurHome.png"));


    //0表示换行，1表示近战路径，2表示远程路径，3表示障碍，
    //4表示我方基地，5表示敌方基地，100表示地图结束
    //绘制地图
    int cnt = 0;
    for (int i = 1; ;i++) {
        for (int j = 1; ; j++){
            if (mymap[cnt] == 0 || mymap[cnt] == 100) break;
            switch (mymap[cnt]) {
            case 1:
                p.drawPixmap((j-1)*P_LEN, (i-1)*P_LEN, P_LEN, P_LEN,QPixmap(":/picture/res/MeleePlace.png"));
                break;
            case 2:
                p.drawPixmap((j-1)*P_LEN, (i-1)*P_LEN, P_LEN, P_LEN,QPixmap(":/picture/res/RPlace.png"));
                break;
            case 3:
                p.drawPixmap((j-1)*P_LEN, (i-1)*P_LEN, P_LEN, P_LEN,QPixmap(":/picture/res/Obstacle.png"));
                break;
            case 4:
                p.drawPixmap((j-1)*P_LEN, (i-1)*P_LEN, P_LEN, P_LEN,QPixmap(":/picture/res/OurHome.png"));
                break;
            case 5:
                p.drawPixmap((j-1)*P_LEN, (i-1)*P_LEN, P_LEN, P_LEN,QPixmap(":/picture/res/ZombieHome.png"));
                break;
            default:
                qDebug() << "Create wrong place!!!" << endl;
                break;
            }
            cnt++;
        }
        if (mymap[cnt] == 100) break;
        cnt++;
    }

    QColor green(0, 0xFF, 0), red(186, 55, 52);
    QPen gpen(green), rpen(red);
    gpen.setWidth(5);
    rpen.setWidth(5);
    double wx, wy, nHP;
    for (int i = 0; i < (int)Mymap.getAllplant().size(); i++) {
        QString itname = Mymap.getAllplant()[i]->getName();
        wx = P_LEN * (Mymap.getAllplant()[i]->getCy() - 1);
        wy = P_LEN * (Mymap.getAllplant()[i]->getCx() - 1);
        nHP = Mymap.getAllplant()[i]->getHP();
        if (itname.compare("PeaShooter") == 0) {
            p.setPen(gpen);
            p.drawLine(wx, wy, wx + P_LEN * (nHP * 1.0 / PeaShooterHP), wy);
            p.setPen(rpen);
            p.drawLine(wx + P_LEN * (nHP * 1.0 / PeaShooterHP), wy, wx + P_LEN, wy);
            p.drawPixmap(wx, wy, P_LEN, P_LEN,
                         QPixmap(":/picture/res/PeaShooter.png"));
        }
        else if (itname.compare("BigMouth") == 0) {
            p.setPen(gpen);
            p.drawLine(wx, wy, wx + P_LEN * (nHP * 1.0 / BigMouthHP), wy);
            p.setPen(rpen);
            p.drawLine(wx + P_LEN * (nHP * 1.0 / BigMouthHP), wy, wx + P_LEN, wy);
            p.drawPixmap(wx, wy - 25, P_LEN, P_LEN + 50,
                         QPixmap(":/picture/res/MeleePlant.png"));
        }
        else if (itname.compare("WallNut") == 0) {
            p.setPen(gpen);
            p.drawLine(wx, wy, wx + P_LEN * (nHP * 1.0 / WallNutHP), wy);
            p.setPen(rpen);
            p.drawLine(wx + P_LEN * (nHP * 1.0 / WallNutHP), wy, wx + P_LEN, wy);
            int cry = 0;
            if (nHP <= 50) {
                cry = 2;
            }
            else if (nHP <= 100) {
                cry = 1;
            }
            p.drawPixmap(wx, wy, P_LEN, P_LEN,
                         QPixmap(QString(":/picture/res/Wallnut%1.png").arg(cry)));
        }
    }

//    绘制僵尸
    for (int i = 0; i < (int)Mymap.getAllzombie().size(); i++) {
        QString itname = Mymap.getAllzombie()[i]->getName();
        wx = P_LEN * (Mymap.getAllzombie()[i]->getCy() - 1);
        wy = P_LEN * (Mymap.getAllzombie()[i]->getCx() - 1);
        nHP = Mymap.getAllzombie()[i]->getHP();
        if (itname.compare("NormalZombie") == 0) {
            p.setPen(gpen);
            p.drawLine(wx, wy, wx + P_LEN * (nHP * 1.0 / NormalZombieHP), wy);
            p.setPen(rpen);
            p.drawLine(wx + P_LEN * (nHP * 1.0 / NormalZombieHP), wy, wx + P_LEN, wy);
            p.drawPixmap(wx, wy, P_LEN, P_LEN,
                         QPixmap(QString(":/picture/res/MeleeZombie%1.png").arg(Mymap.getRoll() % 4)));
        }
        else if (itname.compare("Ballon") == 0) {
            p.setPen(gpen);
            p.drawLine(wx, wy, wx + P_LEN * (nHP * 1.0 / BallonHP), wy);
            p.setPen(rpen);
            p.drawLine(wx + P_LEN * (nHP * 1.0 / BallonHP), wy, wx + P_LEN, wy);
            p.drawPixmap(wx, wy, P_LEN, P_LEN,
                         QPixmap(QString(":/picture/res/RZ%1.png").arg(Mymap.getRoll() % 4)));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    double px = e->y() / P_LEN + 1, py = e->x() / P_LEN + 1;
    QString position = QString("(%1,%2)").arg(px).arg(py);
    Place* clickPlace = Mymap.findplace(position);
    if (!clickPlace->haveplant()) {
        if (clickPlace->getIs_remote()) {
            peaButton->move((py-0.5)*P_LEN,(px-0.5)*P_LEN);
            peaButton->show();
        }
        else if (clickPlace->getIs_melle()) {
            bigmButton->move((py-0.5)*P_LEN,(px-0.5)*P_LEN);
            wallButton->move((py-1)*P_LEN, (px-0.5)*P_LEN);
            wallButton->show();
            bigmButton->show();
        }
    }
}

void MainWindow::addBigMouth() {
    double py = bigmButton->x() / P_LEN + 1, px = bigmButton->y() / P_LEN + 1;
    BigMouth* newbigmouth = new BigMouth;
    Mymap.addCreature(newbigmouth, QString("(%1,%2)").arg(px).arg(py));
    bigmButton->hide();
}

void MainWindow::addPeaShooter() {
    double py = peaButton->x() / P_LEN + 1, px = peaButton->y() / P_LEN + 1;
    PeaShooter* newPlant = new PeaShooter;
    Mymap.addCreature(newPlant, QString("(%1,%2)").arg(px).arg(py));
    wallButton->hide();
    peaButton->hide();
}

void MainWindow::addWallNut() {
    double py = wallButton->x() / P_LEN + 1, px = wallButton->y() / P_LEN + 1;
    WallNut* newPlant = new WallNut;
    Mymap.addCreature(newPlant, QString("(%1,%2)").arg(px).arg(py));
    peaButton->hide();
    wallButton->hide();
}














