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
    explicit bullet(int s, int d, int de, QObject *parent = nullptr);
    void fly();
    int speed, damage, time;
    float deviation;
    bool isHit(const QGraphicsItem &human);
    QGraphicsPixmapItem flash;
};

#endif // BULLET_H
