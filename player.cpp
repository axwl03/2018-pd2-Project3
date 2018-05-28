#include "player.h"

player::player(QObject *parent) : QObject(parent)
{
}
player::player(int character_ID){
    character.append("./picture/killer.png");
    setPixmap(character.at(character_ID));
    setScale(0.5);
    setZValue(1);
    health = 100;
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
