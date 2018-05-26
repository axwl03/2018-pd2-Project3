#include "weapon.h"

weapon::weapon(QObject *parent) : QObject(parent)
{
}
weapon::weapon(int w){
    weapon_ID = w;
    if(weapon_ID == 0){
        shot_interval = 100;
        gun.append("./picture/AWM.png");
    }
    setPixmap(gun.at(0));
}
