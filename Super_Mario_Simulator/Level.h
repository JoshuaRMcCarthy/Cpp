#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
using namespace std;

class Level{

    public:
    Level(unsigned amountOfLevels, unsigned int dimensions, unsigned int coins, unsigned int nothing, unsigned int goombas, unsigned int koopas, unsigned int mushrooms, unsigned int i);
    ~Level();
    void addBoss();
    void addWarpPipe();
    void generateLevel();
    void printLevel();


    char** getLevel();


    char checkNextLevelPos(int xPos,int yPos);
    void updateCharAt(int xPos, int yPos, char c);
    string levelToString();
    char getCharAt(int xPos, int yPos);



    private:
    int chanceOfCoins;
    int chanceOfNothing;
    int chanceOfGoomba;
    int chanceOfKoopa;
    int chanceOfMushroom;
    int levelsMade;
    int gameDimensions;
    int numLevels;
    char** level;

};


#endif