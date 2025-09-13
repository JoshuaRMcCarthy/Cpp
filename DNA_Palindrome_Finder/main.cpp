/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA4
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PalindromeFinder.h"
#include "DNASeq.h"

int main(int argc, char* argv[]) {
    // test for arguments
    if (argc < 2) {
        std::cerr << "Make sure to provide an input file" << std::endl;
        return -1;
    }

    std::string line;
    std::ifstream file;
    std::string inputFile = argv[1];
    file.open(inputFile);

    while (std::getline(file, line)) {  // Get each line
        if (line == "END"){
            continue;
        }
        PalindromeFinder* pal = new PalindromeFinder();
        DNASeq* sequence = new DNASeq(line);
        if(sequence -> isValid()){ // makes sure the sequence is valid
            if(sequence -> isGeneticPalindrome()){ // checks if the sequence is a genetic palindrome
                std::cout << line <<  " - Genetic Palindrome" << std::endl;
            } else {
                std::cout << line <<  " - Not a Genetic Palindrome" << std::endl;
            }
            pal -> findPalindromes(sequence -> getListDNA()); // gets genetic palindrome substrings if there are any
        } else {
            std::cout << line <<  " - INVALID" << std::endl;
        }

        delete pal; // frees memory
        delete sequence; // frees memory
    }
    file.close(); // closes file
    return 0;
}