/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include "World.h"

World::World(unsigned int levels, unsigned int dimensions, unsigned int coins, unsigned int nothing, unsigned int goombas, unsigned int koopas, unsigned int mushrooms){
        world = new Level*[levels];
        gameLevels = levels;

        for (int i = 0; i < gameLevels; ++i){
            world[i] = new Level(levels, dimensions, coins, nothing, goombas, koopas, mushrooms, i);
        }
        levelcounter = 0;
        gameDimensions = dimensions;
}

World::~World() {
    for (int i = 0; i < gameLevels; ++i){
        delete world[i];
    }
    delete[] world;
}

/*
    gets the character from level class at nextPosX, nextPosY
*/
char World::getPosChar(int levelnumber, int nextPosX, int nextPosY){
    return world[levelnumber]->getCharAt(nextPosX, nextPosY);
}

void World::printLevel(int levelNumber) {
    // iterates through the entire level
    world[levelNumber]-> printLevel();
}

void World::printWorld() {
    for (int i = 0; i < gameLevels; ++i) {
        printLevel(i);
    }
}

char** World::getLevel() {
    return world[levelcounter] -> getLevel();
}

int World::getLevelNum() {
    return levelcounter;
}

void World::incrementLevelNum() {
    levelcounter++;
}

/*
    returns the character at the next level at xPos, yPos
*/
char World::checkNextLevelPos(int xPos, int yPos) {
    if (levelcounter == (gameLevels - 1)) {
        return '\0';
    }
    else {
        return world[levelcounter + 1] -> checkNextLevelPos(xPos,yPos);
    }
}

int World::getDimensions() {
    return gameDimensions;
}

/*
    updates the character at a specific position
*/
void World::updateCharAt(int levelNumber, int xPos, int yPos, char c) {
    world[levelNumber] -> updateCharAt(xPos, yPos, c);
}

bool World::isFinalLevel() {
    return (levelcounter == (gameLevels - 1));

}

string World::worldtoString() {
    // prints every level
    string result = "";
    for (int i = 0; i < gameLevels; ++i) {
        result += world[i] -> levelToString();
        result += "\n";
    }
    return result;
}

/*
    returns current level to string
*/
string World::currLeveltoString() {
    string result = "";
    result += world[levelcounter]->levelToString();
    result += ' '; // padding between chars
    result += "\n";
    return result;
}

int World::getGameLevels(){
    return gameLevels;
}