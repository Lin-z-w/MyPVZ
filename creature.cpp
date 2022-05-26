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
    cx = -1;
    cy = -1;
}

Creature::~Creature() {

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

QString Creature::getWay() const
{
    return way;
}

void Creature::setWay(const QString &value)
{
    way = value;
}

double Creature::getFoot() const
{
    return foot;
}

void Creature::setFoot(double value)
{
    foot = value;
}

double Creature::getCx() const
{
    return cx;
}

void Creature::setCx(double value)
{
    cx = value;
}

double Creature::getCy() const
{
    return cy;
}

void Creature::setCy(double value)
{
    cy = value;
}

void Creature::hPDecrease(int d)
{
    HP -= d;
    qDebug() << QString("%1's HP has decrease %2!").arg(name).arg(d);
}

bool Creature::canAttack(Creature *) {
    return true;
}

void Creature::zombieMove() {

}




















