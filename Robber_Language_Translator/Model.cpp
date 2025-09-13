/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA1
*/


#include <iostream>
#include <string>
#include <cctype>
#include "Model.h"


Model::Model() {
    
}

// Destructor: Frees the allocated memory
Model::~Model() {
    
}
std::string Model::translateSingleConsonant(char cons){
   // initializes an empty string then adds the consonant plus 'o' then consonant again
    std::string translation = "";
    translation += cons;
    translation += 'o';
    translation += tolower(cons);
    return translation; 
}

std::string Model::translateSingleVowel(char vowel){
    std::string translation = "";
    translation += vowel;
    return translation;
}
