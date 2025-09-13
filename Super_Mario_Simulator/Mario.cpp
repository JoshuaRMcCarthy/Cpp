/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include "Mario.h"

Mario::Mario(int mLives, World &worldLevel){
    lives = mLives;
    coins = 0;
    powerLevel = 0;
    enemyStreak = 0;
    marioWorld = &worldLevel; 
    gameDimensions = marioWorld->getDimensions();
    lost = false;
    won = false;
    totalMoves = 0;
}

Mario::~Mario(){
}

/* Generates random integer to set as Mario's x and y coordinates. 
Only places Mario in empty spots in the level. */
void Mario::createMario() {
    int level = marioWorld->getLevelNum();
    char** level0 = marioWorld->getLevel(); // gets level 
    // generate random x and y position
    int placementX;
    int placementY; 
    do {
        placementX = rand() % gameDimensions;
        placementY = rand() % gameDimensions;
    }
    while (level0[placementX][placementY] != 'x');

    // change mario in world and update his coordinates
    marioWorld->updateCharAt(level, placementX, placementY, 'H');
    posX = placementX;
    posY = placementY;
}

/* Generates a random integer to determine is Mario moves up, down, left or right.
Mario interacts with whatever is in the coordinate he moved to. */
void Mario::move(int direction) {
    totalMoves++; // increment move counter for final total

    if(direction == 1){ // up
        directionMoved = "UP";

        if(posX - 1 < 0){ // if higher than boundary
            interact(gameDimensions - 1, posY);
        }
        else {
            interact(posX - 1, posY);
        }
    }
    else if(direction == 2){ // down
        directionMoved = "DOWN";

        if(posX + 1 == gameDimensions){ // if less than edge of Y coordinate
            interact(0, posY);
        }
        else {
            interact(posX + 1, posY);
        }
    }
    else if(direction == 3){ // left
        directionMoved = "LEFT";

        if(posY - 1 < 0){ // if less than edge of X coordinate
            interact(posX, gameDimensions - 1);
        }
        else {
            interact(posX, posY - 1);
        }
    }
    else { // right
        directionMoved = "RIGHT";
        
        if(posY + 1 >= gameDimensions){ // if greater than upper edge of x coordinates
            interact(posX, 0);
        }
        else{
            interact(posX, posY + 1);
        }
    }
}

/* Mario interacts with each slot accordingly. Mario's previous position is updated to an 'x' to represent 
whatever was there before is no longer there. */
void Mario::interact(int nextPosX, int nextPosY) {

    int levelNumber = marioWorld->getLevelNum();
    char posChar = marioWorld->getPosChar(levelNumber, nextPosX, nextPosY); // gets char of the next position

    switch(posChar) {
        case 'c':
            addCoin();
            marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
            marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to hero
            posX = nextPosX;
            posY = nextPosY;
            lastInteraction = "Mario collected a coin";
            break;
        case 'm':
            addPL();
            marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
            marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to hero
            posX = nextPosX;
            posY = nextPosY;
            lastInteraction = "Mario ate a mushroom";
            break;
        case 'x':
            marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
            marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to hero
            posX = nextPosX;
            posY = nextPosY;
            lastInteraction = "The position is empty";
            break;
        case 'g':
            if (enemyFight()) {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to hero
                posX = nextPosX;
                posY = nextPosY;
                enemyStreak++;
                lastInteraction = "Mario fought a goomba and won";
            }
            else {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to nothing
                posX = nextPosX;
                posY = nextPosY;
                losePL(); // if mario loses, nothing changes but he loses powerlevel
                enemyStreak = 0;
                lastInteraction = "Mario fought a goomba and lost";
            }
            break;
        case 'k':
            if (enemyFight()) {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to hero
                posX = nextPosX;
                posY = nextPosY;
                enemyStreak++;
                lastInteraction = "Mario fought a koopa and won";
            }
            else {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to nothing
                posX = nextPosX;
                posY = nextPosY;
                losePL(); // if mario loses, nothing changes but he loses powerlevel
                enemyStreak = 0;
                lastInteraction = "Mario fought a koopa and lost";
            }
            break;
        case 'b':
            if (fight()) {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                marioWorld->updateCharAt(levelNumber, nextPosX, nextPosY, 'H'); // reset new space to nothing
                posX = nextPosX;
                posY = nextPosY;
                enemyStreak++;
                lastInteraction = "Mario fought the level boss and won";
                // win condition if mario beats boss at the last level
                if (marioWorld->isFinalLevel()) {
                    won = true;
                }
                else { // move mario to next level (use warppipe method) if not the last level
                    warp();
                }
            }
            else {
                marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
                posX = nextPosX;
                posY = nextPosY;
                lastInteraction = "Mario fought the level boss and lost";
                enemyStreak = 0;
            }
            break;
        case 'w':
            marioWorld->updateCharAt(levelNumber, posX, posY, 'x'); // reset old space to nothing
            warp(); // warp mario to next level
            lastInteraction = "Mario warped";
            break;
        default:
            return;
    }
}

int Mario::getLives(){
    return lives;
}

int Mario::addPL(){
    if(powerLevel < 2){
        powerLevel++; // gains PL
    }
    return powerLevel;
}

void Mario::loseLife(){
    if(lives == 0){
        lost = true; // lose condition
    }
    else{
        lives--;
        powerLevel = 0;
    }
}

void Mario::addLife(){
    lives++;
}

void Mario::losePL(){
    if(powerLevel > 0){
        powerLevel--;
    }
    else{
        loseLife(); // loses life if no PL left to lose
    }
}

int Mario::getPL() {
    return powerLevel;
}

void Mario::addCoin(){
    // adds a life if 20 coins collected
    if(coins == 20){
        addLife();
        coins = 0;
    }
    else{
        coins++;
    }
}

bool Mario::hasWon() {
    return won;
}

bool Mario::hasLost() {
    return lost;
}

int Mario::getPosX() {
    return posX;
}

int Mario::getPosY() {
    return posY;
}

void Mario::setPosX(int positionX) {
    posX = positionX;
}

void Mario::setPosY(int positionY) {
    posY = positionY;
}

string Mario::getLastInteraction() {
    return lastInteraction;
}

int Mario::getCoins(){
    return coins;
}

int Mario::getTotalMoves() {
    return totalMoves;
}

string Mario::getDirectionMoved(){
    return directionMoved;
}


/* sets won boolean variable to true if current level is last level, else will increment level number then 
create a mario for the next level */
void Mario::warp(){
    if (marioWorld->getLevelNum() == marioWorld->getGameLevels()){
        won = true;
    }
    else{
        marioWorld->incrementLevelNum();
        createMario();
    }
}



/* Generates random number. The number generated determines if Mario won or lost. 
If he loses and still has lives, he loses a life and fights again. Otherwise, he loses a life and loses the game. */
bool Mario::fight(){
    int random = rand() % 2;
    if (random == 0){
        return true;
    }
    else {
        if (lives > 1){
            lives -= 1;
            fight();
        }
        else {
            lives -= 1;
            return false;
        }
    }
}


/* Generates random number. The number generated determines if Mario won or lost. 
Returns true if he wins and false if he loses.*/
bool Mario::enemyFight(){
    int random = rand() % 2;
    if (random == 0){
        return true;
    }
    else {
        return false;
    }
}