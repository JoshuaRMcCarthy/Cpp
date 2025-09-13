
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include "Mario.h"
#include <iostream>
#include <fstream>

using namespace std;

class FileProcessor {

    public:
    FileProcessor(string outputFile);
    ~FileProcessor();

    ofstream outFile;

    void processInFile(string inputFile, int* fileInputs);

    void processOutFile(World& world, Mario& mario);

    private:
    int numCounter;
    int* fileInputs;
    World *fileProcessorWorld;
    Mario *fileProcessorMario;



};

#endif