#include <string>
#include <cctype>
// Header guards
#ifndef MODEL_H
#define MODEL_H

class Model {
    
    private:
    
    public:

    Model(); // Default constructor
    ~Model(); // Default destructor

    std::string translateSingleConsonant(char consonant); // Method to translate a single consonant to Robber Language
    std::string translateSingleVowel(char vowel); // Method to translate a single vowel to Robber Language

};

#endif // end of header file & header guard