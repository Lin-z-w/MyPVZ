#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "place.h"
#include <QMap>
#include <QDebug>
#include <QVector>

typedef QMap<QString, Place*> placeMap;
typedef QVector<Creature*> Crtvector;
extern int mymap[];

class GameState
{
private:
    placeMap allplace;
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
    Place* findplace(QString posi);

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
    void computerAction();
    void addCreature(Creature* crt, QString posi);
    Crtvector getAllplant() const;
    Crtvector getAllzombie() const;
    bool getGameover() const;
    placeMap getAllplace() const;
    int getRoll() const;
};

#endif // GAMEMAP_H
