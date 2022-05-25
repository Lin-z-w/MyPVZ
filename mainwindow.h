#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamestate.h"
#include "creature.h"
#include "place.h"
#include "plant.h"
#include "zombie.h"
#include <QTimer>
#include <QMainWindow>

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

public slots:
    void dealGameTimer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer gameTimer;
    GameState Mymap;

};
#endif // MAINWINDOW_H
