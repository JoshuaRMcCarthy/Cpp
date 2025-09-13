/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA4
*/


#include "PalindromeFinder.h"

PalindromeFinder::PalindromeFinder(){ // Default constructor
    lastLength = 4;
}

PalindromeFinder::~PalindromeFinder(){ // Destructor doesnt need anything

}

bool PalindromeFinder::isPalindrome(DblList<char>* seqDNA){ // method checks to see if the sequence given is a palindrome
    DblList<char>* complement = new DblList<char>();
    for (int i = 0; i < seqDNA->size(); ++i){
        switch(seqDNA->get(i)){
            case 'A':
                complement->addBack('T');
                break;
            case 'T':
                complement->addBack('A');
                break;
            case 'C':
                complement->addBack('G');
                break;
            case 'G':
                complement->addBack('C');
                break;
            default:
                return false;
        }
    }
    DblList<char>* backwards = new DblList<char>();
    for (int i = seqDNA->size() - 1; i > -1; --i){
        backwards->addBack(seqDNA->get(i));
    }
    int index = 0;
    while(complement->get(index) == backwards->get(index)){
        if(index == complement->size() - 1){
            return true; // returns true because its at the last index of the linked list and is still matching the backwards with the complement
        }
        ++index;
    }
    return false;
}

string PalindromeFinder::palindromeToString(DblList<char>* palindrome){
    // Returns the palindrome as a string so it can be printed to terminal
    string returnString;
    for (int i = 0; i < palindrome->size(); ++i){
        returnString += palindrome->get(i);
    }
    return returnString;
}

DblList<char>* PalindromeFinder::findPalindromes(DblList<char>* sequence){
    // Finds palindrome substrings in the DNA sequence and prints them to terminal
    int firstLength = 0; // for substring beginning
    int lastLength = 4; // for substring end
    int incLastLength = 4; // to reset the last length to be 4 characters ahead of the new firstLength always
    while(firstLength <= sequence->size() - 4){
        while(lastLength <= sequence -> size() - 1){
            DblList<char>* tempseq = new DblList<char>();
            for(int i = firstLength; i < lastLength; ++i){
                tempseq -> addBack(sequence -> get(i));
            }
            if(isPalindrome(tempseq) && tempseq -> size() != sequence -> size()){
                std::cout << '\t' << "Substring " << palindromeToString(tempseq) << " - Genetic Palindrome" << std::endl;
            }
            lastLength += 2;
        }
        ++firstLength;
        incLastLength++;
        lastLength = incLastLength;
    }
}
