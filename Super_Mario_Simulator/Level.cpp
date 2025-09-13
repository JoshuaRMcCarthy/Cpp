/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include "Level.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Level::Level(unsigned int amountOfLevels, unsigned int dimensions, unsigned int coins, unsigned int nothing, unsigned int goombas, unsigned int koopas, unsigned int mushrooms, unsigned int i){
    if ((coins + nothing + goombas + koopas + mushrooms) != 100) {
        cerr << "Percentages do not add up to 100" << endl;
    }
    else{
        numLevels = amountOfLevels;
        gameDimensions = dimensions;
        chanceOfCoins = coins + 1;
        chanceOfNothing = nothing;
        chanceOfGoomba = goombas;
        chanceOfKoopa = koopas;
        chanceOfMushroom = mushrooms;
        levelsMade = i + 1;

        /*
            creates the 2D array of chars for level
        */
        level = new char*[gameDimensions];
        for (int i = 0; i < gameDimensions; ++i){
            level[i] = new char[gameDimensions];
        }
        /*
            generates what chars are in the level
        */
        generateLevel();

    }
    srand(time(NULL));
}

Level::~Level(){
    for (int i = 0; i < gameDimensions; i++){
        delete[] level[i];
    }
    delete[] level;
}

void Level::printLevel() {
    // iterates through the entire level
    for (int i = 0; i < gameDimensions; ++i) {
        for (int j = 0; j < gameDimensions; ++j) {
            cout << level[i][j] << ' ';
        }
    }
}

char** Level::getLevel() {
    return level;

}


char Level::checkNextLevelPos(int xPos,int yPos){
    return level[xPos][yPos];
}

void Level::updateCharAt(int xPos, int yPos, char c){
    level[xPos][yPos] = c;
}

string Level::levelToString(){
    char** levelArray = getLevel();
    string result;
    for (int i = 0; i < gameDimensions; ++i) {
        for (int j = 0; j < gameDimensions; ++j) {
            result += levelArray[i][j];
 
        }
        result += "\n"; // comment this out if you want the entire 2d array as 1 dimensional string
    }
    return result;
}

/*
    generates the characters in level and adds a boss and warppipe at the end,
    doesnt add warppipe if it is the last level
*/
void Level::generateLevel(){
    for (int i = 0; i < gameDimensions; ++i) {
        // iterate through each char in each line
        for (int j = 0; j < gameDimensions; ++j) {
            
            // generate a random number from 1 - 100
            int generatedChance = rand() % 100 + 1;

            if (generatedChance <= chanceOfCoins){
                updateCharAt(i, j, 'c');
      
    
            }
            else if (generatedChance <= (chanceOfCoins + chanceOfNothing)){
                updateCharAt(i, j, 'x');
         
               
            }
            else if (generatedChance <= (chanceOfCoins + chanceOfNothing + chanceOfGoomba)){
                updateCharAt(i, j, 'g');
 
            
            }
            else if (generatedChance <= (chanceOfCoins + chanceOfNothing + chanceOfGoomba + chanceOfKoopa)){
                updateCharAt(i, j, 'k');

      
            }
            else if (generatedChance <= (chanceOfCoins + chanceOfNothing + chanceOfGoomba + chanceOfKoopa + chanceOfMushroom)){
                updateCharAt(i, j, 'm');

 
            }
            else{
            }
        }
    }
    addBoss();
    addWarpPipe();
}

/*
    adds a boss into the level
*/
void Level::addBoss(){
    int randomRow = (rand() % gameDimensions);
    int randomColumn = (rand() % gameDimensions);
    level[randomRow][randomColumn] = 'b';
}

/*
    adds a warp pipe into the level
*/     
void Level::addWarpPipe(){
    if (numLevels != levelsMade){
        int randomRow = (rand() % gameDimensions);
        int randomColumn = (rand() % gameDimensions);
        if (level[randomRow][randomColumn] == 'b'){
            addWarpPipe();
        }
        else{
            level[randomRow][randomColumn] = 'w';
        }
    }
}

/*
    returns the char at xPos, yPos in the level
*/
char Level::getCharAt(int xPos, int yPos){
    char** levelArray = getLevel();
    return levelArray[xPos][yPos];
}
