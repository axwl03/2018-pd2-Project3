#ifndef ENEMY_H
#define ENEMY_H

#include "human.h"

class Enemy: public Human
{
public:
    Enemy(int h, int character_ID);
    void move();
    virtual void setItemPos();
    void setNewPosition();
    int rx, ry, time;
};

#endif // ENEMY_H
