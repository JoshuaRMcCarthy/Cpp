/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include "FileProcessor.h"
#include "World.h"
#include "Mario.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){

    // test for arguments
    if (argc < 3) {
        std::cerr << "Make sure to provide an input file" << std::endl;
        return -1;
    }

    /*
        fInputs is the int array of size 8 that carries the values from the input file
        by creating a new fileprocessor then running processInFile() with argv[1] being 
        the input file name and then passing in the array fInputs.
    */
    int* fInputs = new int[8];
    FileProcessor* fileProcessor = new FileProcessor(argv[2]);
    fileProcessor->processInFile(argv[1], fInputs); //process input file

    /*
        creating world creates and initializes every level
    */
    World *world = new World(fInputs[0], fInputs[1], fInputs[3], fInputs[4], fInputs[5], fInputs[6], fInputs[7]);
    /*
        creating mario adds mario to the game and processes all the interactions and movements
    */
    Mario *mario = new Mario(fInputs[2], *world);
    bool isGameOver = false;
   
    /*
        this is the gameplay loop and it ends after mario have no lives or the isGameOver variable becomes true
    */
    while(mario->getLives() > 0 && isGameOver == false){
        bool marioWins = false;
        fileProcessor->processOutFile(*world, *mario);
        int randomMove = rand()%4 + 1;
        mario->move(randomMove);
        if (world->isFinalLevel() && mario->hasWon()){
            fileProcessor->processOutFile(*world, *mario);
            isGameOver = true;
        }
        if (mario->getLives() == 0){
            fileProcessor->processOutFile(*world, *mario);
        }
    }

    /*
        deallocates all memory
    */
    delete fileProcessor;
    delete mario;
    delete world;

    return 0;
}