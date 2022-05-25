#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <creature.h>
#include <QString>

class Zombie : public Creature
{
public:
    Zombie(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost = 0);
    bool canAttack(Creature* crt) override;
    void zombieMove() override;
};

class GroundZ : public Zombie
{
public:
    GroundZ(int H, int d, int atra,  QString n,
            bool isr = true, bool isp = false, bool isz = true, bool ifl = true);
};

class FlyZ : public Zombie
{
public:
    FlyZ(int H, int d, int atra,  QString n,
              bool isr = true, bool isp = false, bool isz = true, bool ifl = true);
};

class NormalZombie : public Zombie
{
public:
    NormalZombie(int H = NormalZombieHP, int d = NormalZombieDamage, int atra = NormalZombieAtRa,
                 bool isr = false, bool isp = false, bool isz = true, bool ifl = false, QString n = "NormalZombie", int icost = 0);
};

class RemoteZombie : public Zombie
{
public:
    RemoteZombie(int H = RemoteZombieHP, int d = RemoteZombieDamage, int atra = RemoteZombieAtRa,
                 bool isr = false, bool isp = false, bool isz = true, bool ifl = false, QString n = "RemoteZombie", int icost = 0);
};

class Ballon : public FlyZ
{
public:
    Ballon(int H = BallonHP, int d = BallonDamage, int atra = BallonAtRa, QString n = "Ballon");


};

#endif // ZOMBIE_H
