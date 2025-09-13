/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "SpeakerView.h"
#include "MonoStack.h"

SpeakerView::SpeakerView(string fileName, char o){

    inputFile = fileName;
    cols = 0;
    rows = 0;
    file.open(inputFile);  // Open the file
    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
    typeStack = o;
    
}

SpeakerView::~SpeakerView(){
    for(int i = 0; i < rows; ++i){
        delete[] fileValues[i];
    }
    delete[] fileValues;
    file.close();
}

// Finds the num of rows
void SpeakerView::findNumOfRows(){
    while (std::getline(file, line)) {  // Get each line
        if (line == "BEGIN"){
                continue;
            } else if (line == "END"){
                continue;
            } else{
                ++rows;
            }
    }
}

void SpeakerView::resetFile(){
    // Reset the file stream to the beginning of the file
    file.clear();               // Clear the error and EOF flags
    // ChatGPT showed me how use the line of code below
    file.seekg(0, std::ios::beg);  // Move the pointer back to the start of the file

}

void SpeakerView::findNumOfCols(){
    // This loop here gets the number of cols
    for (int i = 0; i < 2; ++i){
        std::getline(file, line);
        if (line == "BEGIN"){
            continue;
        } else if (line == "END"){
            continue;
        } else{
            std::istringstream iss(line);  // Create a string stream from the line        
            double value;
            while (iss >> value) {  // Extract each double value from the line
            ++cols;
            }   
        }
    }
}

// Creates the fileValues 2D Array
void SpeakerView::create2DArray(){

    fileValues = new double*[rows];
    for (int i = 0; i < rows; ++i){
        fileValues[i] = new double[cols];
    }
}

void SpeakerView::updateDoubleAt(int row, int col, double c){
    fileValues[row][col] = c;
}

double SpeakerView::getDoubleAt(int row, int col){
    return fileValues[row][col];
}

void SpeakerView::addInputsIntoFileValues(){
    // Puts all the doubles from the file input into a 2D array

    for (int i = -1; i < rows; ++i){
        std::getline(file, line);
        if (line == "BEGIN"){
            continue;
        } else if (line == "END"){
            continue;
        } else{

            std::istringstream iss(line);  // Create a string stream from the line        
            for (int j = 0; j < cols; ++j){

                iss >> fileValues[i][j];    // WHY DOES THIS CAUSE A SEG FAULT

            }
        }
    }
}

void SpeakerView::printFileValuesWithIndexs(){
    // PRINTS THE fileInputs array and says which row and col each value is at
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            std::cout << "This is the fileInputs array at row: " << i << ", col: " << j << " :  " << fileValues[i][j] << std::endl;
        }
    }
}

void SpeakerView::printfileValues(){
    // PRINTS THE fileInputs array without the BEGIN and END and shows how it looks in the input file
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            std::cout << fileValues[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double** SpeakerView::getFileValues(){
    return fileValues;
}

void SpeakerView::result(){
    //takes in cols for debugging purposes as of right now i think idrk :)
    findNumOfRows(); // gets number of rows
    resetFile(); // resets the file to read from the beginning again
    findNumOfCols(); // finds the num of columns
    resetFile(); // resets the file to read from the beginning again
    create2DArray(); // creates the 2D array
    addInputsIntoFileValues(); // adds the heights from the file into the 2D array

    MonoStack<double> myStackDouble(10, typeStack); // creating it in the call stack 

    int loopCol = 0; // used to move to the next column when in the while loop
    while(loopCol != cols){  // While the loopCol int doesnt equal the amount of cols in the file
        string heightsWhoCanSee;
        // pushes heights starting from back of the theater to row for proper decreasing monostack
        for(int i = rows - 1; i >= 0; --i){
            myStackDouble.push(fileValues[i][loopCol]);
        }
        /*
            gets the count from monostack to know how many can see and how many to pop
            to get the heights of who can see below and also clear the stack for the next
            column to be pushed to it.
        */
        int numOfWhoCanSee = myStackDouble.getCount();
        for(int i = 0; i < numOfWhoCanSee; ++i){
            // ChatGPT showed me how to use ostringstream
            std::ostringstream oss;
            oss << myStackDouble.pop();

            // Convert the output stream to a string
            heightsWhoCanSee += oss.str();

            if (i <= numOfWhoCanSee-2){
                heightsWhoCanSee += ", ";
            }
        }
        
        // output statement here
        std::cout << "In column " << loopCol << " there are " << numOfWhoCanSee << " that can see. Their heights are: " << heightsWhoCanSee << " inches. " << '\n';
        ++loopCol; // adds 1 to the loopCol so it moved to the next column to grab their values
    }
}
