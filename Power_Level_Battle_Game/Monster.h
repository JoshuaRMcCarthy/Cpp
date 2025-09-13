/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#ifndef MONSTER_CPP
#define MONSTER_CPP
#include <string>
#include <iostream>

using namespace std;

class Monster{

    public:
        Monster();
        Monster(string m_name, int pLevel);
        Monster(Monster& d);
        ~Monster();
        int compare(Monster* otherMonster);
        int getPowerLevel();
        string getMonsterName();
        string name;
        int screamPower;

    private:


};


#endif