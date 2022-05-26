#include "gamestate.h"
#include "MyConstant.h"
#include <QString>

int mymap[] = { 1,1,1,1,2,2,5,5,0,
                1,2,2,1,2,2,2,1,0,
                1,2,2,1,1,1,1,1,0,
                4,3,3,3,3,3,2,3,0,
                4,2,2,2,2,2,2,2,100};   //0表示换行，1表示近战路径，2表示远程路径，3表示障碍，
                                        //4表示我方基地，5表示敌方基地，100表示地图结束
QString way1 = "(1,8)SSWWWWNNWWWSSS";
QString way2 = "(1,7)SSSSWWWWWW";

//判断一个生物是否能放到该格子上
bool canadd(Creature* crt, Place* pl)
{
    bool result = false;
    if (crt->getCanInRemote()) {
        result = true;
    }
    if ((!crt->getCanInRemote()) && (!pl->getIs_remote())) {
        result = true;
    }
    return result;
}

Crtvector GameState::getAllplant() const
{
    return allplant;
}

Crtvector GameState::getAllzombie() const
{
    return allzombie;
}

bool GameState::getGameover() const
{
    return gameover;
}

placeMap GameState::getAllplace() const
{
    return allplace;
}

int GameState::getRoll() const
{
    return roll;
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
            Place* newPlace = new Place(mymap[cnt], (double)i ,(double)j);
            QString placePosition = QString("(%1,%2)").arg(i).arg(j);
            allplace.insert(placePosition,newPlace);
            cnt++;
        }
        if (mymap[cnt] == 100) break;
        cnt++;
    }
    placeMap::iterator initplace = allplace.find(way1.mid(0,5));
    if (initplace == allplace.end()) {
        qDebug() << "Zombie can not begin out of their home!" << endl;
    }
    (*initplace)->setPway(way1.mid(5));
    initplace = allplace.find(way2.mid(0,5));
    if (initplace == allplace.end()) {
        qDebug() << "Zombie can not begin out of their home!" << endl;
    }
    (*initplace)->setPway(way2.mid(5));
}

void GameState::addCreature(Creature* crt, QString posi)
{
    placeMap::iterator addplace = allplace.find(posi);
    if (addplace == allplace.end()) {
        qDebug() << "wrong place position!" << endl;
    }
    else {
        if (canadd(crt, *addplace)) {
            if (crt->getIs_plant()) {
                if ((*addplace)->haveplant()) {
                    qDebug() << "You can't add two plant in the same place!";
                }
                else {
                    (*addplace)->add_creature(crt);
                    allplant.push_back(crt);
                    qDebug() << QString("A %1 is planted!").arg(crt->getName());
                    resource -= crt->getCost();
                }
            }
            else {
                (*addplace)->add_creature(crt);
                qDebug() << QString("A %1 is appeared!").arg(crt->getName());
                allzombie.push_back(crt);
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
    computerAction();
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
    for (Crtvector::iterator it = allplant.begin(); it != allplant.end(); it++) {
        attackZombie(*it);
    }
}

void GameState::attackZombie(Creature* crt)
{
    for (Crtvector::iterator it = allzombie.begin(); it != allzombie.end(); it++) {
        if (crt->canAttack(*it)) {
            (*it)->hPDecrease(crt->getDamage());
            break;
        }
    }
}

void GameState::actionForZombie()
{
    for (Crtvector::iterator it = allzombie.begin(); it != allzombie.end(); it++) {
        attackPlant(*it);
    }
}

void GameState::attackPlant(Creature* crt)
{
    for (Crtvector::iterator it = allplant.begin(); it != allplant.end(); it++) {
        if (crt->canAttack(*it)) {
            (*it)->hPDecrease(crt->getDamage());
            break;
        }
    }
}

QString GameState::nextPlace(Creature *zom) {
    int x = zom->getCx(), y = zom->getCy();
    QChar a = zom->getWay()[0];
    if (a == 'N') {
        x = floor(x);
    }
    else if (a == 'W') {
        y = floor(y);
    }
    else if (a == 'S') {
        x = ceil(x);
    }
    else if (a == 'E') {
        y = ceil(y);
    }
    else {
        qDebug() << "Wrong Direction!!!";
    }
    QString nextPosition = QString("(%1,%2)").arg(x).arg(y);
    placeMap::iterator it = allplace.find(nextPosition);
    if (it == allplace.end()) {
        qDebug() << "The Place in way don't exist!";
    }
    return nextPosition;
}

bool GameState::canMove(Creature* zom) {
    bool result;
    placeMap::iterator it = allplace.find(nextPlace(zom));
    bool nextplant = (*it)->haveplant();
    if (!nextplant) {
        result = true;
    }
    else if (zom->getIs_fly()) {
        if (zom->getWarlike()) {
            result = false;
        }
        else {
            result = true;
        }
    }
    else {
        result = false;
    }
    return result;
}

void GameState::moveForward()
{
    for (Crtvector::iterator it = allzombie.begin(); it != allzombie.end() ;it++) {
        if (canMove(*it)) {
            qDebug() << QString("%1 in (%2,%3) move forward!!!").arg((*it)->getName()).arg((*it)->getCx()).arg((*it)->getCy());
            (*it)->zombieMove();
            if ((*it)->getWay().isEmpty()) {
                gameover = true;
            }
        }
    }
}

void GameState::removeDead()
{
    for (Crtvector::iterator it = allplant.begin(); it != allplant.end(); ) {
        if ((*it)->getHP() <= 0) {
            qDebug() << QString("%1 has dead").arg((*it)->getName());
            int x = (*it)->getCx(), y = (*it)->getCy();
            QString position = QString("(%1,%2)").arg(x).arg(y);
            placeMap::iterator dplace = allplace.find(position);
            (*dplace)->setPlantHere(nullptr);
            delete (*it);
            (*it) = nullptr;
            it = allplant.erase(it);
        }
        else {
            it++;
        }
    }
    for (Crtvector::iterator it = allzombie.begin(); it != allzombie.end(); ) {
        if ((*it)->getHP() <= 0) {
            qDebug() << QString("%1 has dead").arg((*it)->getName());
            delete (*it);
            (*it) = nullptr;
            it = allzombie.erase(it);
        }
        else {
            it++;
        }
    }
}

void GameState::GameOver()
{
    if (gameover) {
        qDebug() << "Game Over!";
    }
}

void GameState::reportGameState()
{
    qDebug() << endl;
    qDebug() << "Roll:" << roll;
    qDebug() << QString("Resource:%1").arg(resource);
    for (Crtvector::iterator it = allplant.begin(); it != allplant.end(); it++) {
        qDebug() << QString("%1 in (%2,%3) HP:%4").arg((*it)->getName())
                    .arg((*it)->getCx()).arg((*it)->getCy()).arg((*it)->getHP());
    }
    for (Crtvector::iterator it = allzombie.begin(); it != allzombie.end(); it++) {
        qDebug() << QString("%1 in (%2,%3) HP:%4").arg((*it)->getName())
                    .arg((*it)->getCx()).arg((*it)->getCy()).arg((*it)->getHP());
    }
}

Place* GameState::findplace(QString posi) {
    return allplace[posi];
}

void GameState::computerAction() {
    if (roll % 20 == 0) {
        NormalZombie* a2;
        Ballon *b2;
        a2 = new NormalZombie;
        b2 = new Ballon;
        addCreature(b2, "(1,7)");
        addCreature(a2, "(1,8)");
    }
}










