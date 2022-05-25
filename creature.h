#ifndef CREATURE_H
#define CREATURE_H
#include "MyConstant.h"
#include <QDebug>
#include <QVector>
#include <QString>

class Place;

class Creature
{
public:
    Creature(int H, int d, int atra, bool cinr, bool isp, bool isz, bool ifl, QString n, int icost);

    //基本行为
    void hPDecrease(int d);


    //set/get接口
    int getAttackRange() const;
    int getDamage() const;
    int getHP() const;
    bool getIs_zombie() const;
    bool getCanInRemote() const;
    bool getIs_plant() const;
    int getCost() const;
    QString getName() const;
    bool getIs_fly() const;
    bool getWarlike() const;
    void setWarlike(bool value);

    QVector<QString> getWay() const;
    void setWay(const QVector<QString> &value);

private:
    int HP, damage, attack_range, cost;
    QString name;
    bool canInRemote, is_plant, is_zombie, is_fly, warlike;
    QVector<QString> way;



};

#endif // CREATURE_H
