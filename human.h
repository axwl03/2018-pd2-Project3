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
    void damaged(int damage);
    virtual void setItemPos() = 0;
    int health, timeInterval;
    weapon *w;
    QGraphicsRectItem *healthbar;
    QVector<QString> character;
};

#endif // HUMAN_H
