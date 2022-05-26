#ifndef CREATURE_H
#define CREATURE_H
#include "MyConstant.h"
#include <algorithm>
#include <QtMath>
#include <QDebug>
#include <QVector>
#include <QString>

class Place;

class Creature
{
public:
    Creature(int H, int d, int atra, bool cinr, bool isp, bool isz, bool ifl, QString n, int icost);
    virtual ~Creature();

    //基本行为
    void hPDecrease(int d);
    virtual bool canAttack(Creature* crt);
    virtual void zombieMove();

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

    QString getWay() const;
    void setWay(const QString &value);

    double getFoot() const;
    void setFoot(double value);

    double getCx() const;
    void setCx(double value);

    double getCy() const;
    void setCy(double value);

protected:
    double foot, cx, cy;
    int HP, damage, attack_range, cost;
    QString name;
    bool canInRemote, is_plant, is_zombie, is_fly, warlike;
    QString way;



};

#endif // CREATURE_H
