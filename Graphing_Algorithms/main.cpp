#include "WGraph.h"
#include "fileProcessor.h"
#include "WGraph.h"
#include <vector>
#include <set>


int main(int argc, char* argv[]){
    if (argc < 2) {
        std::cerr << "Make sure to provide an input file or tournament format" << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];

    std::set<std::set<int>> setOfSets;

    fileProcessor* bob = new fileProcessor(inputFile);
    bob->create2DArray();
    bob->addInputsIntoFileValues();
    int nodes = bob->getNodes();


    WGraph<int> graph(nodes);

    for (int i = 0; i < nodes; i++){
        graph.addVertex(i);
    }


    set<tuple<double, int, int>> edges;

    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j){
            if (bob->fileValues[i][j] != 0.0){
                edges.insert({bob->fileValues[i][j], i, j});
            }
        }
    }

    graph.kruskalsAlgorithm(nodes, edges);
    graph.printAdjacencyMatrix(nodes);

    delete bob;
}

