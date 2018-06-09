#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <weapon.h>

class Human : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Human(int h, QObject *parent = nullptr);
    virtual ~Human();
    void damaged(int damage);
    void changeWeapon();
    virtual void setItemPos() = 0;
    virtual void move() = 0;
    virtual void setNewPosition() = 0;
    int health, timeInterval, time;
    weapon *w, *w1, *w2;
    QGraphicsRectItem *healthbar;
    QVector<QString> character;
};

#endif // HUMAN_H
