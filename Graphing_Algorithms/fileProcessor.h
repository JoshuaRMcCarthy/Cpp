#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

using namespace std;

class fileProcessor{

    public:
        fileProcessor(string fileName);
        ~fileProcessor();
        void findNumOfRows();
        void findNumOfCols();
        void resetFile();
        void create2DArray();
        void addInputsIntoFileValues();
        void createSetofSets();
        int getNodes();
        ifstream file;
        double** fileValues;

        template <typename T>
        friend class WGraph;

    private:
        string inputFile;
        int rows;
        int cols;
        int nodes;
        string line;

};

#endif