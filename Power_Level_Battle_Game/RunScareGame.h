/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#ifndef RUNSCAREGAME_CPP
#define RUNSCAREGAME_CPP
#include "TournamentTree.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class RunScareGame{
    
    public:

        RunScareGame();
        ~RunScareGame();
        void runTournament(string iFile, string oFile, string tFormat);

    private:
        string inFileName;
        string format;
        int rows;


};

#endif