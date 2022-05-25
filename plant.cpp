#include "plant.h"

Plant::Plant(int H, int d, int atra, int icost, bool isr, bool isp, bool isz, QString n, bool ifl)
    : Creature(H, d, atra, isr, isp, isz, ifl, n, icost)
{

}

RemotePlant::RemotePlant(int H, int d, int atra, QString n, int icost, bool isr, bool isp, bool isz)
    : Plant(H, d, atra, icost, isr, isp, isz, n)
{

}

MellePlant::MellePlant(int H, int d, int atra, QString n, int icost, bool isr, bool isp, bool isz)
    : Plant(H, d, atra, icost, isr, isp, isz, n)
{

}

PeaShooter::PeaShooter(int H, int d, int atra, QString n, int icost)
    : RemotePlant(H, d, atra, n, icost)
{

}

BigMouth::BigMouth(int H, int d, int atra, QString n, int icost)
    : MellePlant(H, d, atra, n, icost)
{

}




