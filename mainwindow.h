#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamestate.h"
#include "creature.h"
#include "place.h"
#include "plant.h"
#include "zombie.h"
#include "startwidget.h"
#include <QTimer>
#include <QMainWindow>
#include <QPainter>
#include <QIcon>
#include <QMovie>
#include <QMouseEvent>
#include <QPushButton>
#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

public slots:
    void dealGameTimer();
    void startGame();
    void addPeaShooter();
    void addBigMouth();
    void addWallNut();

private:
    Ui::MainWindow *ui;

    QTimer gameTimer;
    GameState Mymap;

    QDialog* lossGame;
    QPushButton* peaButton, * bigmButton, *wallButton;


    StartWidget sw;

//    QMovie* NormalZgif;

};
#endif // MAINWINDOW_H
