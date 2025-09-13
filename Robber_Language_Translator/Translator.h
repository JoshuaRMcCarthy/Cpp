#include <string>
#include <cctype>
#include <iostream>
#include "Model.h"
// Header guards
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

class Translator {
    
    private:

    Model *modelFile;
    
    public:

    Translator();
    ~Translator();

    std::string translateEnglishWord(std::string word);
    std::string translateEnglishSentence(std::string sentence);



};

#endif // end of header file & header guard