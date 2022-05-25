#include "zombie.h"

Zombie::Zombie(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost)
    : Creature(H, d, atra, isr, isp, isz, ifl, n, icost)
{

}

FlyZ::FlyZ(int H, int d, int atra, QString n, bool isr, bool isp, bool isz, bool ifl)
    : Zombie(H, d, atra, isr, isp, isz, ifl, n)
{

}

NormalZombie::NormalZombie(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost)
    : Zombie(H, d, atra, isr, isp, isz, ifl, n, icost)
{

}

RemoteZombie::RemoteZombie(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost)
    : Zombie(H, d, atra, isr, isp, isz, ifl, n, icost)
{

}

Ballon::Ballon(int H, int d, int atra, QString n) : FlyZ(H, d, atra, n)
{
    setWarlike(false);
}


