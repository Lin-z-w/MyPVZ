#include "place.h"
#include <QDebug>

Place::Place(int a, double x, double y)//1表示近战路径，2表示远程路径，3表示障碍，4表示我方基地
{
    px = x;
    py = y;
    is_melle = false, is_remote = false, is_planthome = false, is_zombiehome = false, is_obstacle = false;
    plantHere = nullptr;
    switch (a) {
    case 1:
        name = "melle";
        is_melle = true;
        break;
    case 2:
        name = "remote";
        is_remote = true;
        break;
    case 3:
        name = "obstacle";
        is_obstacle = true;
        break;
    case 4:
        name = "planthome";
        is_planthome = true;
        break;
    case 5:
        name = "zombiehome";
        is_zombiehome = true;
        break;
    default:
        qDebug() << "Create Wrong Place!" << endl;
        throw 0;
        break;
    }
}

void Place::add_creature(Creature* crt)
{
    crt->setCx(px);
    crt->setCy(py);
    crt->setWay(pway);
    if (crt->getIs_plant()) {
        plantHere = crt;
    }
}

bool Place::getIs_remote() const
{
    return is_remote;
}

bool Place::getIs_planthome() const
{
    return is_planthome;
}

Creature *Place::getPlantHere() const
{
    return plantHere;
}

QString Place::getPway() const
{
    return pway;
}

void Place::setPway(const QString &value)
{
    pway = value;
}

double Place::getPx() const
{
    return px;
}

void Place::setPx(double value)
{
    px = value;
}

double Place::getPy() const
{
    return py;
}

void Place::setPy(double value)
{
    py = value;
}

bool Place::getIs_melle() const
{
    return is_melle;
}

void Place::setPlantHere(Creature *value)
{
    plantHere = value;
}

bool Place::haveplant() {
    return plantHere != nullptr;
}











