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

bool Zombie::canAttack(Creature *crt) {
    QChar targetDirection = way[0];
    int targetx = cx, targety = cy;
    if (targetDirection == 'N') {
        targetx--;
    }
    else if (targetDirection == 'W') {
        targety--;
    }
    else if (targetDirection == 'S') {
        targetx++;
    }
    else if (targetDirection == 'E') {
        targety++;
    }
    else {
        qDebug() << "Wrong Direction!!!";
    }
    if (crt->getCx() == targetx && crt->getCy() == targety) return true;
    return  false;
}

void Zombie::zombieMove() {
    QChar a = way[0];
    if (a == 'N') {
        cx--;
    }
    else if (a == 'W') {
        cy--;
    }
    else if (a == 'S') {
        cx++;
    }
    else if (a == 'E') {
        cy++;
    }
    else {
        qDebug() << "Wrong Direction!!!";
    }
    way.remove(0,1);
}






















