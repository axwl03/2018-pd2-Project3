#include "player.h"

Player::Player(int h, int character_ID): Human(h){
    setPixmap(character.at(character_ID));
    setScale(0.4);
    setZValue(1);
    setData(0, "p");
    w1 = new weapon(1);
    w2 = new weapon(0);
    w = w1;
    healthbar = new QGraphicsRectItem;
    healthbar->setBrush(Qt::green);
}
Player::~Player(){}
void Player::setItemPos(){
    w->setPos(x()+pixmap().width()*scale()/1.6, y()+pixmap().height()*scale()/1.6-w->pixmap().height()*w->scale());
    healthbar->setRect(x()+pixmap().width()*scale()/2-health/2, y()+pixmap().height()*scale()+20, health, 5);
    if(health > 50)
        healthbar->setBrush(Qt::green);
    if(health <= 50 && health > 20)
        healthbar->setBrush(Qt::yellow);
    if(health <= 20)
        healthbar->setBrush(Qt::red);
}
