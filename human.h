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
    explicit Human(QObject *parent = nullptr);
    void damaged(int damage);
    virtual void setItemPos() = 0;
    int health, timeInterval;
    weapon *w;
    QGraphicsRectItem *healthbar;

private:
    QVector<QString> character;
};

#endif // HUMAN_H
