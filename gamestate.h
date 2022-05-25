#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "place.h"
#include <QMap>
#include <QDebug>
#include <QVector>

typedef QMap<QString, Place> placeMap;
typedef QVector<Creature*> Crtvector;

class GameState
{
private:
    placeMap allplace, melleplace, remoteplace, planthome, zombiehome, obstacle;
    Crtvector allplant, allzombie;
    int resource, roll;
    bool gameover;
    QMap<QString, QString> allway;

public:
    GameState();

    void GameOver();
    void removeDead();
    void reportGameState();
    void actionInARoll();

    //Zombies' Aciton
    void actionForPlant();
    bool canMove(Creature* zom);
    QString nextPlace(Creature* zom);
    void moveForward();
    void attackZombie(Creature* crt);

    //Plants' Action
    void actionForZombie();
    void attackPlant(Creature* crt);

    //PC or User Action
    void addCreature(Creature* crt, QString posi);

};

#endif // GAMEMAP_H
