#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <weapon.h>
#include "human.h"

class Player : public Human
{
public:
    Player(int h, int character_ID);
    virtual void setItemPos();
    void changeWeapon();
    weapon *w1, *w2;
};

#endif // PLAYER_H
