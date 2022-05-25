#ifndef PLACE_H
#define PLACE_H

#include "zombie.h"
#include "plant.h"
#include <QVector>
#include <QString>

class Place
{
public:
    Place(int a, int x, int y);//1表示近战路径，2表示远程路径，3表示障碍，4表示我方基地，5表示敌方基地
    void add_creature(const Creature& crt);

    //配合GameState的函数
    void MellezombieOut();
    void MellezombieIn(const Creature& crt);
    void RemotezombieOut();
    void RemotezombieIn(const Creature& crt);
    void removeDead();
    void attackMelleZombie(int damage);
    void attackRemoteZombie(int damage);
    void attackPlant(int damage);

    //report function
    void reportPlant();
    void reportZombie();

    //判断函数
    bool haveMellezombie();
    bool haveRemotezombie();
    bool haveplant();


    //get/set函数
    QVector<Creature> getMelleZombieHere() const;

    QVector<Creature> getPlantHere() const;
    void setPlantHere(const QVector<Creature> &value);

    int getPx() const;
    void setPx(int value);

    int getPy() const;
    void setPy(int value);

    bool getIs_remote() const;

    bool getIs_planthome() const;

    QVector<Creature> getRemotezombieHere() const;

private:
    QString name;
    bool is_melle, is_remote, is_planthome, is_zombiehome, is_obstacle;
    QVector<Creature> plantHere, MellezombieHere, RemotezombieHere;
    int px, py;

};

#endif // PLACE_H
