#ifndef ENEMY_H
#define ENEMY_H

#include "human.h"

class Enemy: public Human
{
public:
    Enemy(int h, int character_ID);
    Enemy(int h, int character_ID, bool e);
    virtual ~Enemy();
    virtual void move();
    virtual void setItemPos();
    virtual void setNewPosition();
    int rx, ry;
};

#endif // ENEMY_H
