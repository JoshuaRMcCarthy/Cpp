/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#include "RunScareGame.h"


RunScareGame::RunScareGame(){ // default constructor
        inFileName = "";
        format = "";
        rows = 0;
}
RunScareGame::~RunScareGame(){ // no destructor code necessary since no memory is being allocated
    
}

void RunScareGame::runTournament(string iFile, string oFile, string tFormat){

    string line;
    ifstream file;
    std::vector<TournamentNode<Monster*>*> bracket; // the bracket that holds the tournamentnodes of monsters
    TournamentTree<Monster*> tree;
    vector<string> names; // to read the names into a vector of strings
    vector<int> powerLevels; // to read the power levels into a vector of ints
    vector<Monster*> monsters; // to create the monster objects using the name and powerlevel vectors
    int power;
    
    file.open(iFile); // open file

    while (std::getline(file, line)) { // gets the names and powerlevels into their appropriate vectors
        string name = "";
        string pow = "";
        for (int i = 0; i < line.length(); ++i){
            if(isalpha(line[i])){
                name += line[i];
            } else if (isdigit(line[i])){
                pow += line[i];
            }
        }
        powerLevels.push_back(stoi(pow));
        names.push_back(name);
    }

    file.close(); // close file

    for(int i = 0; i < names.size(); ++i){ // loops through for the amount of monsters in the game
        Monster* monster = new Monster(names[i], powerLevels[i]); // creates the monster
        monsters.push_back(monster); // adds it to monster vector
        TournamentNode<Monster*>* bob = new TournamentNode<Monster*>(monsters[i]); // creates tournament node based off monster object at index i in monster vector
        bracket.push_back(bob); // adds tournamentnode to tournamentnode bracket vector
    }
    if (tFormat == "single"){ // runs for single bracket battle
        tree.bracketBattle(bracket);
    } else if (tFormat == "double"){ // runs for double bracket battle
       tree.doubleBracketBattle(bracket);
    } else {
        cout << "invalid Tournament Format type, please try again" << endl;
        return;
    }
    tree.saveTreeAsDot(oFile, tree.getmRoot()); // prints to DOTFILE.txt file
}