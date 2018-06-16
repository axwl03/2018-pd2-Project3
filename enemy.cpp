#include "enemy.h"

Enemy::Enemy(int h, int character_ID): Human(h)
{
    setPixmap(character.at(character_ID));
    setScale(0.4);
    setZValue(1);
    setRotation(180);
    setData(0, "enemy");
    if(h == 100)
        w = new weapon(1);
    if(h > 100)
        w = new weapon(4);
    w->setData(0, -10);
    w->setRotation(180);
    healthbar = new QGraphicsRectItem;
    healthbar->setBrush(Qt::green);  
    rx = qrand()%700+100;
    ry = qrand()%100+200;
}
Enemy::Enemy(int h, int character_ID, bool e): Human(h){ //1 vs 1 mode p2
    setPixmap(character.at(character_ID));
    setScale(0.4);
    setZValue(1);
    setRotation(180);
    setData(0, "enemy");
    if(character_ID == 0){
        setScale(0.4);
        w1 = new weapon(2);
        w2 = new weapon(0);
    }
    if(character_ID == 1){
        setScale(0.42);
        w1 = new weapon(2);
        w2 = new weapon(3);
    }
    if(character_ID == 2){
        setScale(0.4);
        w1 = new weapon(1);
        w2 = new weapon(3);
    }
    w1->setRotation(180);
    w1->setData(0, -w1->data(0).toInt());
    w2->setRotation(180);
    w2->setData(0, -w2->data(0).toInt());
    w = w1;
    healthbar = new QGraphicsRectItem;
    healthbar->setBrush(Qt::green);
}
Enemy::~Enemy(){}
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
    healthbar->setRect(x()-pixmap().width()*scale()/2-health/2, y()-pixmap().height()*scale()-20, health, 5);
    if(health > 50)
        healthbar->setBrush(Qt::green);
    if(health <= 50 && health > 20)
        healthbar->setBrush(Qt::yellow);
    if(health <= 20)
        healthbar->setBrush(Qt::red);
}
void Enemy::setNewPosition(){
    rx = qrand()%700+100;
    ry = qrand()%100+200;
}



