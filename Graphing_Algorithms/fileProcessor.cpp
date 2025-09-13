#include "fileProcessor.h"
#include "WGraph.h"

fileProcessor::fileProcessor(string fileName){
    inputFile = fileName;
    cols = 0;
    rows = 0;
    file.open(inputFile);  // Open the file
    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
    std::getline(file, line);
    nodes = std::stoi(line);
    fileValues = new double*[nodes];
    for (int i = 0; i < nodes; ++i){
        fileValues[i] = new double[nodes];
    }
}

fileProcessor::~fileProcessor(){
    for(int i = 0; i < rows; ++i){
        delete[] fileValues[i];
    }
    delete[] fileValues;
    file.close();
}

void fileProcessor::resetFile(){
    // Reset the file stream to the beginning of the file
    file.clear();               // Clear the error and EOF flags
    // ChatGPT showed me how use the line of code below
    file.seekg(0, std::ios::beg);  // Move the pointer back to the start of the file

}


// Creates the fileValues 2D Array
void fileProcessor::create2DArray(){
    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j){
            fileValues[i][j] = -1.0;
        }
    }
}

void fileProcessor::addInputsIntoFileValues(){
    // Puts all the doubles from the file input into a 2D array

    for (int i = 0; i < nodes; ++i){
        std::getline(file, line);
        if (line == "END"){
            continue;
        } else{

            std::istringstream iss(line);  // Create a string stream from the line      
            for (int j = 0; j < nodes; ++j){
                double value;

                iss >> value;
                fileValues[i][j] = value;

            }
        }
    }
}

int fileProcessor::getNodes(){
    return nodes;
}



