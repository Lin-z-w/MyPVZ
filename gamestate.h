#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "place.h"
#include <QMap>
#include <QDebug>

typedef QMap<QString, Place> placeMap;

class GameState
{
private:
    placeMap allplace, melleplace, remoteplace, planthome, zombiehome, obstacle;
    int resource, roll;
    bool gameover;

public:
    GameState();

    void moveForward();
    void GameOver();
    void removeDead();
    void reportGameState();
    void actionInARoll();

    //Zombies' Aciton
    void actionForPlant();
    void attackZombie(Creature& crt, int x, int y);

    //Plants' Action
    void actionForZombie();
    void attackPlant(Creature& crt, int x, int y);

    void addCreature(const Creature& crt, QString posi);

};

#endif // GAMEMAP_H
