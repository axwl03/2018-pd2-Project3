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
    virtual ~Player();
    virtual void move(){}
    virtual void setItemPos();
    virtual void setNewPosition(){}
};

#endif // PLAYER_H
