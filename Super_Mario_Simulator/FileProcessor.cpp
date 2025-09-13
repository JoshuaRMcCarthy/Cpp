/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include "FileProcessor.h"

FileProcessor::FileProcessor(string outputFile) {
    outFile.open(outputFile);
    numCounter = 0;
}

FileProcessor::~FileProcessor() {
    outFile.close(); // closes output file
}

/* Reads input file and outputs values into an array */
void FileProcessor::processInFile(string inputFile, int* fileInputs){
            
    ifstream fileToRead;          
    string fileLine;
    int fileSize = 8; // set size because we know the amount of lines in the file

    fileToRead.open(inputFile);

    if (!fileToRead.is_open()){ //if file can't be opened {
        cerr << "Couldn't open " << inputFile << endl;
        return;
    }

    if (fileToRead.is_open()) {
        for (int i = 0; i < fileSize; i++){ //read line by line into array of file inputs
            fileToRead >> fileInputs[i]; // integer array that will hold the values for the game to run
        }
    }
    fileToRead.close();
    if (fileToRead.fail()){
        cerr << "file didnt close properly" << endl;
    }
}


/* Prints world and level to output file. Every move is logged in the output file named whatever is passed in */
void FileProcessor::processOutFile(World& world, Mario& mario){ // This function is for after every mario move
    fileProcessorWorld = &world;
    fileProcessorMario = &mario;
    if (outFile.is_open()) {
        if (numCounter == 0){
            outFile << "================================================================================" << endl;
            outFile << fileProcessorWorld->worldtoString() << "\n" << endl;
            outFile << "================================================================================" << endl;
            mario.createMario();
            outFile << "Mario is starting in position: (" << fileProcessorMario->getPosX() << ","  << fileProcessorMario->getPosY() << ")." << endl;

        }
        else{
            outFile << "================================================================================" << endl;
            outFile << "\n" << fileProcessorWorld->currLeveltoString() << "\n" << "LeveL: " << fileProcessorWorld->getLevelNum() << ". Mario is at position: (" << fileProcessorMario->getPosX() << ", " << fileProcessorMario->getPosY() << "). Mario is at power level " << fileProcessorMario->getPL() << ". Mario has " << fileProcessorMario->getLives() << " lives left. Mario has " << fileProcessorMario->getCoins() << " coins. Mario has moved " << fileProcessorMario->getDirectionMoved() << " and " << fileProcessorMario->getLastInteraction() << ".\n";
            outFile << "================================================================================" << endl;
        }
        numCounter += 1;
    }
    else {
        cerr << "Output file didn't open correctly" << endl; // error (output)
    }
}

