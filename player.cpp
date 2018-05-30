#include "player.h"

player::player(QObject *parent) : QObject(parent)
{
}
player::player(int character_ID):timeInterval(0){
    character.append("./picture/killer.png");
    setPixmap(character.at(character_ID));
    setScale(0.5);
    setZValue(1);
    health = 100;
    w = new weapon(1);
    healthbar = new QGraphicsRectItem;
    healthbar->setBrush(Qt::green);
}
void player::damaged(int damage){
    health -= damage;
}
void player::move(int tx, int ty){
    if(tx - x() > 0)
        setPos(x()+1,y());
    if(tx - x() < 0)
        setPos(x()-1,y());
    if(ty - y() > 0)
        setPos(x(), y()+1);
    if(ty - y() < 0)
        setPos(x(), y()-1);
}
void player::setItemPos(){
    w->setPos(x()+pixmap().width()*scale()/1.6, y()+pixmap().height()*scale()/1.6-w->pixmap().height()*w->scale());
    healthbar->setRect(x()+pixmap().width()*scale()/2-50, y()-30, health, 5);
    if(health <= 50 && health > 20)
        healthbar->setBrush(Qt::yellow);
    if(health <= 20)
        healthbar->setBrush(Qt::red);
}

