/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TournamentTree.h"
#include "RunScareGame.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Make sure to provide an input file or tournament format" << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];
    std::string tournamentFormat = argv[2];
    RunScareGame* Tournament = new RunScareGame();
    Tournament->runTournament(inputFile, "DOTFile.txt", tournamentFormat);
    
    delete Tournament; // deletes all created memory

    return 0;
    
}