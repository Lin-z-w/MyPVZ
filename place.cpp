#include "place.h"
#include <QDebug>

Place::Place(int a, int x, int y)//1表示近战路径，2表示远程路径，3表示障碍，4表示我方基地
{
    px = x;
    py = y;
    is_melle = false, is_remote = false, is_planthome = false, is_zombiehome = false, is_obstacle = false;
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


void Place::add_creature(const Creature& crt)
{
    if (crt.getIs_plant()) {
        plantHere.push_back(crt);
        qDebug() << "A " << crt.getName() <<" is planted!";
    }
    if (crt.getIs_zombie()) {
        if (crt.getCanInRemote()) {
            RemotezombieHere.push_back(crt);
            qDebug() << "A " << crt.getName() <<" appear!";
        }
        else {
            MellezombieHere.push_back(crt);
            qDebug() << "A " << crt.getName() <<" appear!";
        }
    }
}

QVector<Creature> Place::getPlantHere() const
{
    return plantHere;
}

void Place::setPlantHere(const QVector<Creature> &value)
{
    plantHere = value;
}

int Place::getPx() const
{
    return px;
}

void Place::setPx(int value)
{
    px = value;
}

int Place::getPy() const
{
    return py;
}

void Place::setPy(int value)
{
    py = value;
}

bool Place::getIs_remote() const
{
    return is_remote;
}

bool Place::getIs_planthome() const
{
    return is_planthome;
}

QVector<Creature> Place::getRemotezombieHere() const
{
    return RemotezombieHere;
}


QVector<Creature> Place::getMelleZombieHere() const
{
    return MellezombieHere;
}

bool Place::haveplant()
{
    return !plantHere.empty();
}

bool Place::haveMellezombie()
{
    return !MellezombieHere.empty();
}

bool Place::haveRemotezombie()
{
    return !RemotezombieHere.empty();
}

void Place::MellezombieOut()
{
    if (MellezombieHere.empty()) {
        qDebug() << "There is no melle zombie to move!!!";
    }
    MellezombieHere.pop_back();
}

void Place::MellezombieIn(const Creature& crt)
{
    MellezombieHere.push_back(crt);
}

void Place::RemotezombieOut()
{
    if (RemotezombieHere.empty()) {
        qDebug() << "There is no melle zombie to move!!!";
    }
    RemotezombieHere.pop_back();
}

void Place::RemotezombieIn(const Creature& crt)
{
    RemotezombieHere.push_back(crt);
}

void Place::removeDead()
{
    if (haveplant()) {
        if (plantHere.front().getHP() <= 0) {
            qDebug() << QString("%1 has dead").arg(plantHere.front().getName());
            plantHere.clear();
        }
    }
    else if (haveMellezombie()) {
        QVector<Creature>::iterator it = MellezombieHere.begin();
        while (it != MellezombieHere.end()) {
            if (it->getHP() <= 0) {
                it = MellezombieHere.erase(it);
                continue;
            }
            it++;
        }
    }
    else if (haveRemotezombie()) {
        QVector<Creature>::iterator it = RemotezombieHere.begin();
        while (it != RemotezombieHere.end()) {
            if (it->getHP() <= 0) {
                it = RemotezombieHere.erase(it);
                continue;
            }
            it++;
        }
    }
}

void Place::attackPlant(int damage)
{
    if (!haveplant()) {
        qDebug() << "There is no plant to attack.";
    }
    else {
        plantHere.front().hPDecrease(damage);
    }
}

void Place::attackMelleZombie(int damage)
{
    if (!haveMellezombie()) {
        qDebug() << "There is no zombie to attack.";
    }
    else {
        MellezombieHere.back().hPDecrease(damage);
    }
}

void Place::attackRemoteZombie(int damage)
{
    if (!haveRemotezombie()) {
        qDebug() << "There is no zombie to attack.";
    }
    else {
        RemotezombieHere.back().hPDecrease(damage);
    }
}

void Place::reportPlant()
{
    if (haveplant()) {
        qDebug() << QString("%1 in (%2,%3) HP:%4").arg(plantHere.front().getName())
                    .arg(px).arg(py).arg(plantHere.front().getHP());
    }
}

void Place::reportZombie()
{
    if (haveMellezombie()) {
        for (int i = 0; i < (int)(MellezombieHere.size()); i++){
             qDebug() << QString("%1 in (%2,%3) HP:%4").arg(MellezombieHere[i].getName())
                    .arg(px).arg(py).arg(MellezombieHere[i].getHP());
        }
    }
    if (haveRemotezombie()) {
        for (int i = 0; i < (int)(RemotezombieHere.size()); i++){
             qDebug() << QString("%1 in (%2,%3) HP:%4").arg(RemotezombieHere[i].getName())
                    .arg(px).arg(py).arg(RemotezombieHere[i].getHP());
        }
    }
}









