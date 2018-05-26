#include "player.h"

player::player(QObject *parent) : QObject(parent)
{
}
player::player(int character_ID){
    character.append("./picture/player.png");
    setPixmap(character.at(character_ID));
    setScale(0.5);
    setZValue(1);
    health = 100;
}
void player::damaged(int damage){
    health -= damage;
    qDebug() << health;
    if(health <= 0){
        this->scene()->removeItem(this);
        delete this;
    }
}
