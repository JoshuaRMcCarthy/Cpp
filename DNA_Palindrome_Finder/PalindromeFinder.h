#ifndef PALINDROMEFINDER_H
#define PALINDROMEFINDER_H
#include <string>
#include <iostream>
#include <fstream>
#include "DblList.h"

using namespace std;

class PalindromeFinder{

    public:
        PalindromeFinder();
        ~PalindromeFinder();

        bool isPalindrome(DblList<char>* seqDNA);
        string palindromeToString(DblList<char>* palindrome);
        DblList<char>* findPalindromes(DblList<char>* sequence);

    private:
        int lastLength;



};

#endif