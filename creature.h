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

    int getCx() const;
    void setCx(int value);

    int getCy() const;
    void setCy(int value);

    QString getWay() const;
    void setWay(const QString &value);

protected:
    int HP, damage, attack_range, cost, cx, cy;
    QString name;
    bool canInRemote, is_plant, is_zombie, is_fly, warlike;
    QString way;



};

#endif // CREATURE_H
