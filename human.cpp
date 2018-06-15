#include "human.h"

Human::Human(int h, QObject *parent) : QObject(parent), health(h), timeInterval(0), time(0)
{
    character.append("./picture/killer.png");
    character.append("./picture/bone.png");
}
void Human::damaged(int damage){
    health -= damage;
}
void Human::changeWeapon(){
    if(w == w1){
        w2->setVisible(w->isVisible());
        w = w2;
    }
    else if(w == w2){
        w1->setVisible(w->isVisible());
        w = w1;
    }
}
Human::~Human(){}
