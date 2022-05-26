#ifndef PLACE_H
#define PLACE_H

#include "zombie.h"
#include "plant.h"
#include <QVector>
#include <QString>

class Place
{
public:
    Place(int a, double x, double y);//1表示近战路径，2表示远程路径，3表示障碍，4表示我方基地，5表示敌方基地
    void add_creature(Creature* crt);

    //配合GameState的函数

    //判断函数
    bool haveplant();

    //get/set函数
    bool getIs_remote() const;

    bool getIs_planthome() const;

    Creature *getPlantHere() const;
    void setPlantHere(Creature *value);

    QString getPway() const;
    void setPway(const QString &value);

    double getPx() const;
    void setPx(double value);

    double getPy() const;
    void setPy(double value);

    bool getIs_melle() const;

private:
    QString name, pway;
    bool is_melle, is_remote, is_planthome, is_zombiehome, is_obstacle;
    Creature* plantHere;
    double px, py;

};

#endif // PLACE_H
