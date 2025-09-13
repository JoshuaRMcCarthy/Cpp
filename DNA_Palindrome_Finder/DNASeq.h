#ifndef DNASEQ_H
#define DNASEQ_H
#include "DblList.h"
#include "PalindromeFinder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class DNASeq{

    public:
        DNASeq();
        DNASeq(string DNAsequence);
        ~DNASeq();

        DblList<char>* complement();
        DblList<char>* substring(int s, int e);
        bool isGeneticPalindrome();
        DblList<char>* backwards();
        DblList<char>* getListDNA();
        bool isValid();

    private:
        string DNA;
        DblList<char>* ListDNA;




};

#endif
