/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA1
*/


#include "FileProcessor.h"
#include "Model.h"
#include "Translator.h"

FileProcessor::FileProcessor() {
    translator = new Translator();
}

FileProcessor::~FileProcessor() {
    delete translator;
}


void FileProcessor::processFile(std::string iFile, std::string oFile){

    std::ifstream inFile;
    inFile.open(iFile);

    if (inFile.is_open()) {
        
        std::string eSentence = ""; // needed for translation

        std::string robberLanguage = ""; // after translation

        // reads from input file to append everything to a sentence
        std::string readLine = "";
        while (getline(inFile, readLine)) { // reads the input file and puts all of it into a sentence
            // add the english sentence
            eSentence += htmlEnglish(readLine); 
            // makes and append after being translated to Robber Language
            robberLanguage += htmlRobberLanguage(translator->translateEnglishSentence(readLine));
        }

        inFile.close(); // closes the input file

        std::string OutputForHTML = HTMLhead(); // makes the HTML file string below
        OutputForHTML += eSentence + "<br/><br/>" + robberLanguage + "\n</body>\n</html>"; // br is for a space between the english and the translation

        std::ofstream outFile; // creates output file stream
        outFile.open(oFile); // opens output file
        if (outFile.is_open()) {
        
            outFile << OutputForHTML; // writes to output file
            outFile.close(); // closes output file
        }
        else {
            std::cerr << "Output file didn't open correctly" << std::endl; // error (output)
        }
        
    }
    else {
        std::cerr << "Input file didn't open correctly" << std::endl; // error (input)
    }

    return;
}


std::string FileProcessor::HTMLhead() {
    // initalizes the header and body for HTML
    std::string creating = "";
    creating += "<!DOCTYPE html>\n<html>\n<head>\n<title>English to Robber Language</title>\n</head>\n<body>\n";
    return creating;
}


std::string FileProcessor::htmlEnglish(std::string english) {
    // makes the bold for english
    std::string adding = "<p><b>" + english + "</b><br></p>\n";
    return adding;
}

std::string FileProcessor::htmlRobberLanguage(std::string robberLanguage) {
    // makes italics div for the robber language translation
    std::string adding = "<p><i>" + robberLanguage + "</i><br></p>\n";
    return adding;
}

std::string FileProcessor::HTMLending() {
    // ends the HTML <>
    std::string ending = "";
    ending += "\n</body>\n</html>";
    return ending;
}

