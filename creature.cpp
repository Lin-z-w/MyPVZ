#include "creature.h"

Creature::Creature(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost)
{
    HP = H;
    damage = d;
    attack_range = atra;
    name = n;
    canInRemote = isr;
    is_plant = isp;
    is_zombie = isz;
    is_fly = ifl;
    warlike = true;
    cost = icost;
}

int Creature::getAttackRange() const
{
    return attack_range;
}

int Creature::getDamage() const
{
    return damage;
}

int Creature::getHP() const
{
    return HP;
}

bool Creature::getIs_zombie() const
{
    return is_zombie;
}

bool Creature::getCanInRemote() const
{
    return canInRemote;
}

bool Creature::getIs_plant() const
{
    return is_plant;
}

int Creature::getCost() const
{
    return cost;
}

QString Creature::getName() const
{
    return name;
}

bool Creature::getIs_fly() const
{
    return is_fly;
}

bool Creature::getWarlike() const
{
    return warlike;
}

void Creature::setWarlike(bool value)
{
    warlike = value;
}

QVector<QString> Creature::getWay() const
{
    return way;
}

void Creature::setWay(const QVector<QString> &value)
{
    way = value;
}

void Creature::hPDecrease(int d)
{
    HP -= d;
    qDebug() << QString("%1's HP has decrease %2!").arg(name).arg(d);
}



















