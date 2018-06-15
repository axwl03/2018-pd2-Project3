#include "player.h"

Player::Player(int h, int character_ID): Human(h){
    setPixmap(character.at(character_ID));
    setZValue(1);
    setData(0, "p");
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
