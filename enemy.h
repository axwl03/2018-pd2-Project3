#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit enemy(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ENEMY_H
