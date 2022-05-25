#include "gamestate.h"
#include "MyConstant.h"
#include <QString>

int mymap[] = { 4,2,2,2,2,2,2,5,0,
                4,1,1,1,1,1,1,5,0,
                4,2,2,2,2,2,2,5,0,
                4,2,2,2,2,2,2,5,0,
                4,2,2,2,2,2,2,5,0,
                4,2,2,2,2,2,2,5,100};   //6行8列，0表示换行，1表示近战路径，2表示远程路径，3表示障碍，
                                        //4表示我方基地，5表示敌方基地，100表示地图结束

//判断一个生物是否能放到该格子上
bool canadd(const Creature& crt, const Place& pl)
{
    bool result = false;
    if (crt.getCanInRemote() && pl.getIs_remote()) {
        result = true;
    }
    if ((!crt.getCanInRemote()) && (!pl.getIs_remote())) {
        result = true;
    }
    return result;
}

GameState::GameState()
{
    resource = INITRESOURSE;
    roll = 0;
    gameover = false;
    int cnt = 0;
    for (int i = 1; ;i++) {
        for (int j = 1; ; j++){
            if (mymap[cnt] == 0 || mymap[cnt] == 100) break;
            Place newPlace(mymap[cnt], i ,j);
            QString placePosition = QString("(%1,%2)").arg(i).arg(j);
            allplace.insert(placePosition,newPlace);
            switch (mymap[cnt]) {
            case 1:
                melleplace.insert(placePosition,newPlace);
                break;
            case 2:
                remoteplace.insert(placePosition,newPlace);
                break;
            case 3:
                obstacle.insert(placePosition,newPlace);
                break;
            case 4:
                planthome.insert(placePosition,newPlace);
                break;
            case 5:
                zombiehome.insert(placePosition,newPlace);
                break;
            default:
                qDebug() << "Create wrong place!!!" << endl;
                break;
            }
            cnt++;
        }
        if (mymap[cnt] == 100) break;
        cnt++;
    }
}

void GameState::addCreature(const Creature &crt, QString posi)
{
    placeMap::iterator addplace = allplace.find(posi);
    if (addplace == allplace.end()) {
        qDebug() << "wrong place position!" << endl;
    }
    else {
        if (canadd(crt, *addplace)) {
            if (crt.getIs_plant()) {
                if (addplace->haveplant()) {
                    qDebug() << "You can't add two plant in the same place!";
                }
                else {
                    addplace->add_creature(crt);
                    resource -= crt.getCost();
                }
            }
            else {
                addplace->add_creature(crt);
            }
        }
        else {
            qDebug() << "Add wrong type creature to the place!";
        }
    }
}

void GameState::actionInARoll()
{
    roll++;
    actionForPlant();
    actionForZombie();
    removeDead();
    moveForward();
    reportGameState();
    GameOver();
    qDebug() << endl;
}

void GameState::actionForPlant()
{
    for (placeMap::iterator it = allplace.begin(); it != allplace.end(); it++) {
        if ((*it).haveplant()) {
            attackZombie((*it).getPlantHere().front(), (*it).getPx(), (*it).getPy());
        }
    }
}

void GameState::attackZombie(Creature &crt, int x, int y)
{
    QString searchPlaceName;
    if (!crt.getCanInRemote()) {
        for (int i = 0; i < crt.getAttackRange(); i++) {
            y++;
            searchPlaceName = QString("(%1,%2)").arg(x).arg(y);
            placeMap::iterator searchPlace = allplace.find(searchPlaceName);
            if (searchPlace == allplace.end()) {
                continue;
            }
            else {
                if (searchPlace->haveMellezombie()){
                    searchPlace->attackMelleZombie(crt.getDamage());
                    break;
                }
                else if (searchPlace->haveRemotezombie()) {
                    searchPlace->attackRemoteZombie(crt.getDamage());
                    break;
                }
            }
        }
    }
    else {
        for (int i = y - crt.getAttackRange(); i <= y + crt.getAttackRange(); i++) {
            for (int j = x - crt.getAttackRange(); j <= x + crt.getAttackRange(); j++) {
                searchPlaceName = QString("(%1,%2)").arg(j).arg(i);
                placeMap::iterator searchPlace = allplace.find(searchPlaceName);
                if (searchPlace == allplace.end()) {
                    continue;
                }
                else {
                    if (searchPlace->haveMellezombie()){
                        searchPlace->attackMelleZombie(crt.getDamage());
                        break;
                    }
                    else if (searchPlace->haveRemotezombie()) {
                        searchPlace->attackRemoteZombie(crt.getDamage());
                        break;
                    }
                }
            }
        }
    }
}

void GameState::actionForZombie()
{
    for (placeMap::iterator it = allplace.begin(); it != allplace.end(); it++) {
        if ((*it).haveMellezombie()) {
            for (int i = 0; i < (int)((*it).getMelleZombieHere().size()); i++) {
                attackPlant((*it).getMelleZombieHere()[i], it->getPx(), it->getPy());
            }
        }
        if ((*it).haveRemotezombie()) {
            for (int i = 0; i < (int)((*it).getRemotezombieHere().size()); i++) {
                attackPlant((*it).getRemotezombieHere()[i], it->getPx(), it->getPy());
            }
        }
    }
}

void GameState::attackPlant(Creature &crt, int x, int y)
{
    QString searchPlaceName;
    for (int i = 0; i < crt.getAttackRange(); i++) {
        y--;
        searchPlaceName = QString("(%1,%2)").arg(x).arg(y);
        placeMap::iterator searchPlace = allplace.find(searchPlaceName);
        if (searchPlace == allplace.end()) {
            continue;
        }
        else {
            if (searchPlace->haveplant()) {
                searchPlace->attackPlant(crt.getDamage());
                break;
            }
        }
    }
}

void GameState::moveForward()
{
    placeMap::iterator it = allplace.begin();
    int x = 0, y = 0;
    while (it != allplace.end()) {
        x = it->getPx(), y = it->getPy();
        QString nextPosition = QString("(%1,%2)").arg(x).arg(y-1);
        placeMap::iterator nextplace = allplace.find(nextPosition);
        if (nextplace == allplace.end() || nextplace->haveplant() || !(it->haveMellezombie())) {
            it++;
            continue;
        }
        while (it->haveMellezombie()) {
            nextplace->MellezombieIn(it->getMelleZombieHere().back());
            it->MellezombieOut();
        }
        if (nextplace->getIs_planthome()) gameover = true;
        qDebug() << "Zombie move forward!!!";
        it++;
    }
}

void GameState::removeDead()
{
    placeMap::iterator it = allplace.begin();
    while (it != allplace.end()) {
        it->removeDead();
        it++;
    }
}

void GameState::GameOver()
{
    if (gameover) {
        qDebug() << "Game Over!";
        exit(-1);
    }
}

void GameState::reportGameState()
{
    qDebug() << endl;
    qDebug() << "Roll:" << roll;
    qDebug() << QString("Resource:%1").arg(resource);
    placeMap::iterator it = allplace.begin();
    while (it != allplace.end()) {
        if (it->haveplant()) {
            it->reportPlant();
        }
        else if (it->haveMellezombie()) {
            it->reportZombie();
        }
        it++;
    }
}












