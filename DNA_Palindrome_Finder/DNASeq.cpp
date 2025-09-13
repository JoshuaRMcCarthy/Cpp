/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA4
*/


#include "DNASeq.h"


DNASeq::DNASeq(){
    // Default Constructor
    ListDNA = new DblList<char>();
    DNA = "";
}

DNASeq::~DNASeq(){
    // Destructor
    delete ListDNA;
}

DNASeq::DNASeq(string DNAsequence){
    // Overloaded Constructor
    ListDNA = new DblList<char>();
    DNA = DNAsequence;
    for (int i = 0; i < DNAsequence.length(); ++i){
        ListDNA->addBack(DNA[i]);
    }
}


DblList<char>* DNASeq::complement(){
    //returns a DNA Sequence representing the complement.
    DblList<char>* complement = new DblList<char>();
    for (int i = 0; i < ListDNA->size(); ++i){
        switch(ListDNA->get(i)){
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
        }
    }
    return complement;

}

DblList<char>* DNASeq::backwards(){
    // finds the backwards sequence, this function is useless, I made it by mistake
    DblList<char>* backwards = new DblList<char>();
    for (int i = DNA.length() - 1; i > -1; --i){
        backwards->addBack(ListDNA->get(i)); //ListDNA->get(i);
    }
    return backwards;
}

DblList<char>* DNASeq::substring(int s, int e){
    //returns a DNA Sequence based on the substring from position s (inclusive) to position e (exclusive).
    DblList<char>* subString = new DblList<char>();
    for (int i = s; i < e; ++i){
        subString->addBack(ListDNA->get(i)); //ListDNA->get(i);
    }
    return subString;
}

bool DNASeq::isGeneticPalindrome(){
    //returns true if the sequence is a genetic palindrome and false otherwise.
    PalindromeFinder* pal = new PalindromeFinder();
    return pal -> isPalindrome(ListDNA);
}

DblList<char>* DNASeq::getListDNA(){ // getter method
    return ListDNA;
}

bool DNASeq::isValid(){ // checks to make sure the dna sequence is made up of ATCG and more than 3 characters
    if(DNA.length() < 4){
        return false;
    }
    for (int i = 0; i < DNA.length(); ++i){
        char sChar = DNA[i];
        if(sChar == 'A'){
            continue;
        } else if(sChar == 'T'){
            continue;
        } else if(sChar == 'C'){
            continue;
        } else if(sChar == 'G'){
            continue;
        } else {
            return false;
        }
    }
    return true;
}
