#ifndef WGRAPH_H
#define WGRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <limits> // For numeric limits to indicate infinity for conn matrix
#include <iostream>
#include <tuple>
#include <algorithm>

#include "fileProcessor.h"

using namespace std;

// CLASS TO REPRESENT EACH VERTEX
template <typename T>
class Vertex {
public:
    T name; // Each vertex has a 'name' of type T
    Vertex(T n); // Constructor
    ~Vertex(); // Destructor
};

template <typename T>
Vertex<T>::Vertex(T n) { name = n; } // Assign 'name' during construction

template <typename T>
Vertex<T>::~Vertex() {} // No specific cleanup needed for Vertex

// CLASS TO REPRESENT A WEIGHTED GRAPH
template <typename T>
class WGraph {
public:
    WGraph(int sz); // Constructor to initialize graph of a given size
    ~WGraph(); // Destructor to clean up dynamic allocations

    void addVertex(T name);
    void addEdge(T name1, T name2, double weight);
    void removeEdge(T name1, T name2);
    bool areAdjacent(T name1, T name2);
    double getWeight(T name1, T name2);
    std::vector<T> dfs(T startVertex);
    std::vector<T> bfs(T startVertex);
    int findIslands();
    double cheapestCost(T i, T j); // Find the cheapest path between two vertices, uses calcFW()
    void calcFW(); // Calculate the Floyd-Warshall algorithm to find shortest paths

    void kruskalsAlgorithm(int n, set<std::tuple<double, int, int> >& edges);
    void unionSets(int u, int v, vector<int>& parent, vector<int>& rank);
    int findParent(int node, vector<int>& parent);

    void printAdjacencyMatrix(int nodes);



    void processFile();

    /*
    void WGraph<T>::kruskals();
    std::set<std::set<int>> setOfSets;
    */

private:
    int m_size; // Maximum number of vertices in the graph
    double** m_adj; // 2D array representing adjacency matrix for edge weights
    std::vector<Vertex<T> > m_vertices; // List of vertices
    std::unordered_map<T, int> m_nameToIndex; // Map to track each vertex's index by name

    // FW code
    bool recalcFW;               // Flag to determine if Floyd-Warshall needs recalculation
    double** m_conn;                // Matrix to store shortest paths between all pairs of vertices
};

// CONSTRUCTOR
template <typename T>
WGraph<T>::WGraph(int sz) {
    m_size = sz;
    m_adj = new double*[m_size];
    m_conn = new double*[m_size]; // Allocate memory for m_conn
    for (int i = 0; i < m_size; ++i) {
        m_adj[i] = new double[m_size];
        m_conn[i] = new double[m_size];
        for (int j = 0; j < m_size; ++j) {
            m_adj[i][j] = 0.0; // std::numeric_limits<int>::max() indicates infinity/ no edge
            m_conn[i][j] = std::numeric_limits<int>::max(); // Initialize m_conn with infinity
        }
        m_conn[i][i] = 0; // Distance to self is 0
    }
    recalcFW = true; // Initially set to true

}

// DESTRUCTOR
template <typename T>
WGraph<T>::~WGraph() {
    for (int i = 0; i < m_size; ++i) {
        delete[] m_adj[i];
        delete[] m_conn[i];
    }
    delete[] m_adj;
    delete[] m_conn;
}

// Add a new vertex to the graph
template <typename T>
void WGraph<T>::addVertex(T name) {
    if (m_vertices.size() < m_size) {
        m_vertices.push_back(Vertex<T>(name));
        m_nameToIndex[name] = m_vertices.size() - 1;
    } else {
        std::cerr << "Graph capacity reached. Cannot add more vertices." << std::endl;
    }
}

// Add an edge with a weight between two vertices
template <typename T>
void WGraph<T>::addEdge(T name1, T name2, double weight) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        m_adj[i][j] = weight;
        m_adj[j][i] = weight; // Symmetric for undirected graph
    } else {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
    }
}

// Remove an edge between two vertices
template <typename T>
void WGraph<T>::removeEdge(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        m_adj[i][j] = std::numeric_limits<int>::max();
        m_adj[j][i] = std::numeric_limits<int>::max();
    } else {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
    }
}

// Check if two vertices are adjacent
template <typename T>
bool WGraph<T>::areAdjacent(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        return m_adj[i][j] != std::numeric_limits<int>::max(); // True if weight is not infinity/ std::numeric_limits<int>::max()
    }
    return false;
}

// Get the weight of an edge
template <typename T>
double WGraph<T>::getWeight(T name1, T name2) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        return m_adj[i][j];
    }
    return std::numeric_limits<int>::max(); // Return std::numeric_limits<int>::max() if no edge exists
}

// DFS traversal
template <typename T>
std::vector<T> WGraph<T>::dfs(T startVertex) {
    std::vector<T> visited_order;
    if (m_nameToIndex.count(startVertex) == 0) return visited_order;

    int startIndex = m_nameToIndex[startVertex];
    std::stack<int> stk;
    std::set<int> visited;

    stk.push(startIndex);
    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();

        if (visited.count(current) != 0) continue;

        visited.insert(current);
        visited_order.push_back(m_vertices[current].name);

        for (int k = 0; k < m_size; ++k) {
            if (m_adj[current][k] != std::numeric_limits<int>::max() && visited.count(k) == 0) {
                stk.push(k);
            }
        }
    }
    return visited_order;
}

// BFS traversal
template <typename T>
std::vector<T> WGraph<T>::bfs(T startVertex) {
    std::vector<T> visited_order;
    if (m_nameToIndex.count(startVertex) == 0) return visited_order;

    int startIndex = m_nameToIndex[startVertex];
    std::queue<int> q;
    std::set<int> visited;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        visited_order.push_back(m_vertices[current].name);

        for (int k = 0; k < m_size; ++k) {
            if (m_adj[current][k] != std::numeric_limits<int>::max() && visited.count(k) == 0) {
                q.push(k);
                visited.insert(k);
            }
        }
    }
    return visited_order;
}
 

// Floyd-Warshall Algorithm
template <typename T>
void WGraph<T>::calcFW() {
    std::cout << "*** Calculating Floyd-Warshall *** " << std::endl;

    // Step 1: Initialize the connection matrix (m_conn) with the adjacency matrix (m_adj)
    // This step sets the initial shortest paths between directly connected nodes.
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            // If there's an edge between i and j (indicated by m_adj[i][j] != std::numeric_limits<int>::max()),
            // copy the weight of the edge into m_conn.
            m_conn[i][j] = m_adj[i][j];
        }
        // The distance from a node to itself is always infinity, so we set m_conn[i][i] = std::numeric_limits<int>::max().
        m_conn[i][i] = std::numeric_limits<int>::max();
    }

    // Step 2: Apply the Floyd-Warshall algorithm to compute shortest paths
    // This triple nested loop iterates through all possible paths in the graph,
    // considering each node (im) as an intermediate point.

    for (int im = 0; im < m_size; ++im) { // Loop over all nodes as intermediate points
        for (int source = 0; source < m_size; ++source) { // Loop over all nodes as source points
            for (int sink = 0; sink < m_size; ++sink) { // Loop over all nodes as sink points
                // Step 2.1: Skip invalid cases
                // If either the source to intermediate (source -> im) or
                // intermediate to sink (im -> sink) path is unreachable,
                // then we skip the update for source -> sink.
                if (m_conn[source][im] == std::numeric_limits<int>::max() ||
                    m_conn[im][sink] == std::numeric_limits<int>::max()) {
                    continue; // No valid path exists through the intermediate node
                }

                // Step 2.2: Update shortest path using the intermediate node
                // If the path from source -> sink through im is shorter than the current
                // shortest path from source -> sink, update it.
                if (m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]) {
                    // Update the shortest path from source to sink
                    m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
                }
            }
        }
    }

    // Step 3: Reset the flag to indicate that Floyd-Warshall results are up-to-date
    recalcFW = false;
}

// Find the cheapest path
template <typename T>
double WGraph<T>::cheapestCost(T i, T j) {
    if (m_nameToIndex.count(i) == 0 || m_nameToIndex.count(j) == 0) {
        throw std::invalid_argument("One or both vertices not found in the graph.");
    }

    int source = m_nameToIndex[i];
    int sink = m_nameToIndex[j];

    if (recalcFW) {
        calcFW();
    }

    return m_conn[source][sink];
}



// NEW ADDED CODE FOR PA6


template <typename T>
void WGraph<T>::printAdjacencyMatrix(int nodes){
    // PRINTS THE fileInputs array without the BEGIN and END and shows how it looks in the input file
    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j){
            std::cout << m_adj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


// Function to find the parent of a node in the disjoint set
template <typename T>
int WGraph<T>::findParent(int node, vector<int>& parent) {
    if (parent[node] == node) return node; // If the node is its own parent
    return parent[node] = findParent(parent[node], parent); // Path compression
}

// Function to perform union of two sets
template <typename T>
void WGraph<T>::unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal's Algorithm to find MST
template <typename T>
void WGraph<T>::kruskalsAlgorithm(int n, set<std::tuple<double, int, int> >& edges) {
    vector<int> parent(n);
    vector<int> rank(n, 0);

    // Initialize disjoint set
    for (int i = 0; i < n; ++i) parent[i] = i;

    vector<std::tuple<double, int, int> > mst; // To store the MST edges
    int mstWeight = 0;

    // Iterate over sorted edges
    for (const std::tuple<double, int, int>& edge : edges) {
        double weight = std::get<0>(edge);
        int u = std::get<1>(edge);
        int v = std::get<2>(edge);
        if (findParent(u, parent) != findParent(v, parent)) {
            mst.push_back({weight, u, v});
            addEdge(u, v, weight);
            mstWeight += weight;
            unionSets(u, v, parent, rank);
        }
    }

    // Print the MST and its weight
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const std::tuple<double, int, int>& edge : mst) {
        double weight = std::get<0>(edge);
        int u = std::get<1>(edge);
        int v = std::get<2>(edge);
        cout << "(" << u << ", " << v << ") with weight " << weight << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

#endif








// OLD CODE





/*
template <typename T>
void WGraph<T>::kruskals(){
    
    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j){
            std::set<int> set1;
            if (fileValues[i][j] != 0.0){
                set1.insert(j);
            }
            setOfSets.insert(set1);

        }
    }

    // create a 2D array where each level is an edge and is ordered top to bottom by which is lowest weight
    // Ex:
    // 1  2  1.0
    // 2  4  2.0
    // 3  6  4.0
    // honestly i dont even know

    for (const auto& inner_set : setOfSets) {
        
        for (const auto& element : inner_set) {

        }
    }

}
*/

