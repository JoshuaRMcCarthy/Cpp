/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA1
*/

#include <iostream>
#include "Translator.h"

Translator::Translator(){  // default constructor
    modelFile = new Model();
}

Translator::~Translator(){ // default destructor
    delete modelFile;
}

std::string Translator::translateEnglishWord(std::string word) {

    std::string translation = ""; // creates an empty string
    for (int i = 0; i < word.size(); ++i) { // iterates through each character in the string based off the strings size
        switch(tolower(word[i])) { // puts the char to lowercase then checks through each case of if its one of the consonants
            case 'b':
            case 'c':
            case 'd':
            case 'f':
            case 'g':
            case 'h':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                translation += modelFile->translateSingleConsonant(word[i]); // if a consonant, will turn into Robber Language
                break; //                                                       piece and be appended to the translation

            default:
                translation += modelFile->translateSingleVowel(word[i]); // default case assumes that if its not a consonant then
                break;                                                   // it must be a vowel, so its appended to the translation
        }
    }
    return translation; // returns the string that is the Robber Language translation of the english word
}

std::string Translator::translateEnglishSentence(std::string sentence) {
    std::string translation = "";
    int beginningOfWord = 0; // tracks index of where a word begins

    for(int i = 0; i < sentence.size(); ++i) {

       
        if (sentence[i] == ' ') { // looks for where a word ends by finding the space character that seperates them

            // gets the word by substringing the word out of the original string based off the index of the
            // beginning of the word and where the index of i in sentence is ' '.
            std::string word = sentence.substr(beginningOfWord, i - beginningOfWord); 

            translation += translateEnglishWord(word) + " "; // translates the word then preserves the space

            beginningOfWord = i + 1; // prevents error by moving the value to 1 after the index of where the space was
        }
         /* make sure to translate the last word if there are any characters left after a space
            the else if (as opposed to if) prevents an error when a space is the last char in a sentence
         */
        else if (i == sentence.size() - 1) {  // translates the last word
            std::string word = sentence.substr(beginningOfWord, i);
            translation += translateEnglishWord(word);
        }

    }

    return translation;
}
