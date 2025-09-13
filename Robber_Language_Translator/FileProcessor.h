
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include "Translator.h"

class FileProcessor {

    public:
        FileProcessor();
        ~FileProcessor();

        void processFile(std::string iFile, std::string oFile);

    private:
        std::string htmlEnglish(std::string english);
        std::string htmlRobberLanguage(std::string rovarspraket);
        std::string HTMLhead();
        std::string HTMLending();
        Translator *translator;

};

#endif