#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class SpeakerView{
    
    public:
    SpeakerView(string fileName, char o);
    ~SpeakerView();
    void printFileValuesWithIndexs();
    void printfileValues();
    void addInputsIntoFileValues();
    void create2DArray();
    void findNumOfRows();
    void findNumOfCols();
    void resetFile();
    void openFile();
    double** getFileValues();
    void updateDoubleAt(int row, int col, double c);
    double getDoubleAt(int row, int col);
    void result();
    ifstream file;

    private:
        string inputFile;
        double** fileValues;
        int rows;
        int cols;
        string line;
        char typeStack;

};

#endif