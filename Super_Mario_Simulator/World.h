#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include "Level.h"
using namespace std;

class World {

    public:
        World(unsigned int L,
                unsigned int N,
                unsigned int coins,
                unsigned int nothing,
                unsigned int goombas,
                unsigned int koopas,
                unsigned int mushrooms);
        ~World();
        char** getLevel();
        char checkNextLevelPos(int xPos, int yPos);
        void printLevel(int levelNumber);
        void printWorld();
        string worldtoString();
        string currLeveltoString();
        int getLevelNum();
        void incrementLevelNum();
        int getDimensions();
        void updateCharAt(int levelNumber, int xPos, int yPos, char c);
        bool isFinalLevel();
        Level *level;

        char getPosChar(int levelnumber, int nextPosX, int nextPosY);
        int getGameLevels();

        // DELETE LATER (NOT NEEDED)
        //void findHero();
        //int getHeroXCoord();
        //int getHeroYCoord();

    private:
        //int heroXCoord;
        //int heroYCoord;
        int gameDimensions;
        // char*** world;
        Level** world;
        int levelcounter;
        int gameLevels;
        char** makeLevel();

};

#endif