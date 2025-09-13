#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include "World.h"
//#include "Enemy.h"

using namespace std;

class Mario {

    public:
    World *marioWorld;
    Mario(int mLives, World &worldLevel);
    ~Mario();
    void createMario();
    void move(int direction);
    void interact(int nextPosX, int nextPosY);
    int getLives();
    int addPL();
    void loseLife();
    void addLife();
    void losePL();
    int getPL();
    void addCoin();
    bool hasWon();
    bool hasLost();
    int getPosX();
    int getPosY();
    void setPosX(int positionX);
    void setPosY(int positionY);
    string getLastInteraction();
    int getCoins();
    int getTotalMoves();
    string getDirectionMoved();


    void warp();
    bool fight();
    bool enemyFight();


    private:
    int lives;
    int coins;
    int powerLevel;
    int enemyStreak;
    int posX;
    int posY;
    int gameDimensions;
    bool lost;
    bool won;
    int totalMoves;
    string lastInteraction;
    string directionMoved;

};

#endif