#ifndef PLANT_H
#define PLANT_H
#include "creature.h"
#include <QString>

class Plant : public Creature
{
public:
    Plant(int H, int d, int atra, int icost, bool cinr, bool isp, bool isz, QString n, bool ifl = false);

private:

};

class MellePlant : public Plant
{
public:
    MellePlant(int H, int d, int atra, QString n, int icost, bool cinr = false, bool isp = true, bool isz = false);
};

class RemotePlant : public Plant
{
public:
    RemotePlant(int H, int d, int atra, QString n, int icost, bool cinr = true, bool isp = true, bool isz = false);
};

//对地对空、面前范围攻击，属于远程单位
class PeaShooter : public RemotePlant
{
public:
    PeaShooter(int H = PeaShooterHP, int d = PeaShooterDamage, int atra = PeaShooterAtRa,
               QString n = "PeaShooter", int icost = 10);
    bool canAttack(Creature * crt) override;

};

//对地、四周进行攻击，属于近战单位
class BigMouth : public MellePlant
{
public:
    BigMouth(int H = BigMouthHP, int d = BigMouthDamage, int atra = BigMouthAtRa,
             QString n = "BigMouth", int icost = 10);
    bool canAttack(Creature * crt) override;
};

#endif // PLANT_H
