#include "enemy.h"

Enemy::Enemy(int h, int character_ID): Human(h), time()
{
    character.append("./picture/killer.png");
    setPixmap(character.at(character_ID));
    setScale(0.4);
    setZValue(1);
    setRotation(180);
    setData(0, "enemy");
    w = new weapon(1);
    w->setData(0, -10);
    w->setRotation(180);
    healthbar = new QGraphicsRectItem;
    healthbar->setBrush(Qt::green);  
    rx = qrand()%700+100;
    ry = qrand()%100+200;
}
void Enemy::move(){
    if(rx - x() > 0)
        setPos(x()+1,y());
    if(rx - x() < 0)
        setPos(x()-1,y());
    if(ry - y() > 0)
        setPos(x(), y()+1);
    if(ry - y() < 0)
        setPos(x(), y()-1);
}
void Enemy::setItemPos(){
    w->setPos(x()-pixmap().width()*scale()/1.6, y()-pixmap().height()*scale()/1.6+w->pixmap().height()*w->scale());
    healthbar->setRect(x()-pixmap().width()*scale()/2-50, y()-pixmap().height()*scale()-20, health, 5);
    if(health <= 50 && health > 20)
        healthbar->setBrush(Qt::yellow);
    if(health <= 20)
        healthbar->setBrush(Qt::red);
}
void Enemy::setNewPosition(){
    rx = qrand()%700+100;
    ry = qrand()%100+200;
}


