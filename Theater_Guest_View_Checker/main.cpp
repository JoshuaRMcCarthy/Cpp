/*
Joshua McCarthy
002449270
jomccarthy@chapman.edu
CPSC350-03
PA2
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SpeakerView.h"

int main(int argc, char* argv[]) {
    // test for arguments
    if (argc < 2) {
        std::cerr << "Make sure to provide an input file" << std::endl;
        return -1;
    }

    SpeakerView* theater = new SpeakerView(argv[1], 'd');
    theater->result();
    delete theater;
    return 0;
}