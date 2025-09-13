/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#include "Monster.h"

Monster::Monster(){
    name = "";
    screamPower = 0;
}

Monster::Monster(string m_name, int pLevel){ // overloaded
    name = m_name;
    screamPower = pLevel;
}

Monster::Monster(Monster& d){ // copy constructor
    name = d.name;
    screamPower = d.screamPower;
}

Monster::~Monster(){
    
}



int Monster::compare(Monster* otherMonster){ // overloaded compare method that compares the powerlevels and returns -1 or 1 based off who wins
    int thisPowerLevel = screamPower;
    int otherPowerLevel = otherMonster->screamPower;
    if (thisPowerLevel == otherPowerLevel){
        return 0;
    }
    if (thisPowerLevel < otherPowerLevel){
        return -1;
    }
    if (thisPowerLevel > otherPowerLevel){
        return 1;
    }
}
