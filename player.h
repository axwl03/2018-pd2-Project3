#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

class player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);
    player(int character_ID);
    void damaged(int damage);
    int health;
    void move(int tx, int ty);
private:
    QVector<QString> character;

};

#endif // PLAYER_H
