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
    setFoot(0.1);
}

RemoteZombie::RemoteZombie(int H, int d, int atra, bool isr, bool isp, bool isz, bool ifl, QString n, int icost)
    : Zombie(H, d, atra, isr, isp, isz, ifl, n, icost)
{

}

Ballon::Ballon(int H, int d, int atra, QString n) : FlyZ(H, d, atra, n)
{
    setWarlike(false);
    setFoot(0.1);
}

bool Zombie::canAttack(Creature *crt) {
    bool result = true;
    QChar targetDirection = way[0];
    float targetx = crt->getCx(), targety = crt->getCy();
    if (targetDirection == 'N') {
        if (targety == cy && targetx - cx >= 0 && targetx - cx <= 1) {
            result = true;
        }
        else {
            result = false;
        }
    }
    else if (targetDirection == 'W') {
        if (targetx == cx && cy - targety >= 0 && cy - targety <= 1) {
            result = true;
        }
        else {
            result = false;
        }
    }
    else if (targetDirection == 'S') {
        if (targety == cy && cx - targetx >= 0 && cx - targetx <= 1) {
            result = true;
        }
        else {
            result = false;
        }
    }
    else if (targetDirection == 'E') {
        if (targetx == cx && targety - cy >= 0 && targety - cy <= 1) {
            result = true;
        }
        else {
            result = false;
        }
    }
    else {
        qDebug() << "Wrong Direction!!!";
    }
    return result;
}

void Zombie::zombieMove() {
    QChar a = way[0];
    if (a == 'N') {
        cx -= foot;
    }
    else if (a == 'W') {
        cy -= foot;
    }
    else if (a == 'S') {
        cx += foot;
    }
    else if (a == 'E') {
        cy += foot;
    }
    else {
        qDebug() << "Wrong Direction!!!";
    }
    if (abs(cx - round(cx)) < foot/2 && abs(cy - round(cy)) < foot/2) {
        //qDebug() << cx << " " << cy;

        //qDebug() << "---------------------------------------------------------";
        cx = round(cx);
        cy = round(cy);
        way.remove(0,1);
    }
}






















