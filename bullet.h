#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include "player.h"

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit bullet(int s, int d, QObject *parent = nullptr);
    void fly();
    int speed, damage;
};

#endif // BULLET_H
