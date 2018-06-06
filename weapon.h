#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit weapon(QObject *parent = nullptr);
    weapon(int w);
    int weapon_ID, shot_interval;
    QMediaPlayer sound;

private:
    QVector<QString> gun;
};

#endif // WEAPON_H
