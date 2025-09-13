/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H

#include "TournamentNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

template <typename T>
class TournamentTree{
    public:
        TournamentTree();
        virtual ~TournamentTree();
        // contains: is this data d in the tree?
        bool contains(T d); // recursive version
        bool iterContains(T d); // iterative version
        // print methods 
        void printInOrder(); // least to greatest order 
        void printPostOrder(); 

        // insert 
        void insert(T d);

        // remove
        void remove(T key);

        // size
        int size();

        // extrema
        T max();
        T min(); 
        T naiveMedian(); // return the root, will be median if tree happens to be perfectly balanced & full

        // participation from lecture 19, height of tree
        int maxDepth();

        // getter for m_root
        TournamentNode<T>* getmRoot();
        

        void bracketBattle(std::vector<TournamentNode<T>*> bracket);
        void doubleBracketBattle(std::vector<TournamentNode<T>*> bracket);
        void doubleBracketBattleWinnerHelper(std::vector<TournamentNode<T>*> bracket);
        void doubleBracketBattleLoserHelper(std::vector<TournamentNode<T>*> bracket);

        void saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode);
        void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID);


    private:
        TournamentNode<T>* m_root; 
        TournamentNode<T>* m_loser_root;
        int m_size;
        std::vector<TournamentNode<T>*> loserBracket;
        // helper methods for recursive methods 
        void destroyTree(TournamentNode<T>* node);

        bool containsHelper(TournamentNode<T>* n, T d);
        void printIOHelper(TournamentNode<T>* n);
        void printPOHelper(TournamentNode<T>* n);

        void insertHelper(TournamentNode<T>*& n, T& d);

        T getMaxHelper(TournamentNode<T>* n);
        T getMinHelper(TournamentNode<T>* n);

        void findTarget (T key, TournamentNode<T>*& target, TournamentNode<T>*& parent);
        TournamentNode<T>* getSuccessor (TournamentNode<T>* rightChild);

        int maxDepthHelper(TournamentNode<T>* subRoot);
};


// CONSTRUCTOR
template <typename T>
TournamentTree<T>::TournamentTree(){
    m_root = NULL;
    m_loser_root = NULL;
    m_size = 0;
}

// DESTRUCTOR
template <typename T>
TournamentTree<T>::~TournamentTree(){
    // TO DO
    destroyTree(m_root); // Helper function to delete all nodes

}
// ACTIVITY:
template <typename T>
void TournamentTree<T>::destroyTree(TournamentNode<T>* node) {
    if (node != NULL) {
        destroyTree(node->m_left);  // Recursively delete the left subtree
        destroyTree(node->m_right); // Recursively delete the right subtree
        delete node;                // Delete the current node
    }
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::getmRoot(){
    return m_root;
}

// SIZE 
template <typename T>
int TournamentTree<T>::size(){
    return m_size;
}

template <typename T>
void TournamentTree<T>::bracketBattle(std::vector<TournamentNode<T>*> bracket) {
    std::vector<TournamentNode<T>*> nextBracket; // creates the next bracket of winners battling

    for (int i = 0; i < bracket.size() - 1; i += 2){ // loops through amount of monsters in bracket
        int val = bracket[i]->m_data->compare(bracket[i+1]->m_data); // compares their power levels in overloaded method
        if (val < 0){ // if val is less than 0, the node inside compare method won and winner pointers are assigned to a new node created off a copy of a dereferenced node object which won. then the root is reassigned as the winner
            bracket[i]->winner = new TournamentNode<T>(*bracket[i+1]);
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i]->winner);
            TournamentNode<T>* bob = new TournamentNode<T>(*bracket[i], 1);
            loserBracket.push_back(bob);
            m_root = bracket[i]->winner;
            m_root -> m_left = bracket[i];
            m_root -> m_right = bracket[i + 1];
        } else if (val > 0){ // if val is greater than 0, node outside of compare method won and same thing happens but the winner is assigned to the node outside.
            bracket[i]->winner = new TournamentNode<T>(*bracket[i]); 
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i]->winner);
            TournamentNode<T>* bob = new TournamentNode<T>(*bracket[i+1], 1);
            loserBracket.push_back(bob);
            m_root = bracket[i]->winner;
            m_root -> m_left = bracket[i];
            m_root -> m_right = bracket[i + 1];
        } else {
            std::cout << "bracket index " << i << " and " << i + 1 << " are equal, the val made was: " << val << endl;
        }
        if(bracket.size() % 2 == 1 && i + 1 == bracket.size() - 2){ // checks if this is the last iteration of the loop to add the value at the end of the nextBracket vector
            int bracketLength = bracket.size() - 1;
            bracket[bracketLength]->winner = new TournamentNode<T>(*bracket[bracketLength]);
            bracket.push_back(bracket[bracketLength]->winner);
            m_root = bracket[bracketLength]->winner;
            m_root -> m_right = bracket[bracketLength];
        }
    }
    if(nextBracket.size() != 1){
        bracketBattle(nextBracket); // recursive
    }
}

template <typename T>
void TournamentTree<T>::doubleBracketBattle(std::vector<TournamentNode<T>*> bracket){
    // for double bracket copy and paste the code above and then make another bracket for
    // losers where the loser gets added to another bracket. after the loop is over,
    // take the root nodes of both the winners and losers bracket and compare them.
    // Then set the pointer to the winner.
    doubleBracketBattleWinnerHelper(bracket); // creates winner tree and loser bracket
    doubleBracketBattleLoserHelper(loserBracket); // uses loser bracket made above and creates loser tree
    if((m_root -> getMonster()->compare(m_loser_root -> getMonster())) < 0){ // compares the root of winner and loser tree to make the root of a single tree be the grand champion
        m_root -> winner = new TournamentNode<T>(*m_loser_root);
        m_root -> winner -> m_left = m_root;
        m_root -> winner -> m_right = m_loser_root;
        m_loser_root -> winner = m_root -> winner;
        m_root = m_root -> winner;
    } else if((m_root -> getMonster()->compare(m_loser_root -> getMonster())) > 0){
        m_root -> winner = new TournamentNode<T>(*m_root);
        m_root -> winner -> m_left = m_root;
        m_root -> winner -> m_right = m_loser_root;
        m_loser_root -> winner = m_root -> winner;
        m_root = m_root -> winner;
    } else {
        cout << "something bad happened when comparing the double bracket battle" << endl;
    }
}



template <typename T>
void TournamentTree<T>::doubleBracketBattleWinnerHelper(std::vector<TournamentNode<T>*> bracket){ // same idea as bracket battle but uses an overloaded copy constructor for creating a new node for the loser bracket so that the left and right pointers dont carry over
    std::vector<TournamentNode<T>*> nextBracket;

    for (int i = 0; i < bracket.size() - 1; i += 2){
        int val = bracket[i]->m_data->compare(bracket[i+1]->m_data);
        if (val < 0){
            bracket[i]->winner = new TournamentNode<T>(*bracket[i+1]);
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i]->winner);
            TournamentNode<T>* bob = new TournamentNode<T>(*bracket[i], 1);
            loserBracket.push_back(bob);
            m_root = bracket[i]->winner;
            m_root -> m_left = bracket[i];
            m_root -> m_right = bracket[i + 1];

        } else if (val > 0){
            bracket[i]->winner = new TournamentNode<T>(*bracket[i]); 
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i]->winner);
            TournamentNode<T>* bob = new TournamentNode<T>(*bracket[i+1], 1);
            loserBracket.push_back(bob);
            m_root = bracket[i]->winner;
            m_root -> m_left = bracket[i];
            m_root -> m_right = bracket[i + 1];
        } else {
            std::cout << "bracket index " << i << " and " << i + 1 << " are equal, the val made was: " << val << endl;
        }
        if(bracket.size() % 2 == 1 && i + 1 == bracket.size() - 2){ // checks if this is the last iteration of the loop to add the value at the end of the nextBracket vector
            int bracketLength = bracket.size() - 1;
            bracket[bracketLength]->winner = new TournamentNode<T>(*bracket[bracketLength]);
            bracket.push_back(bracket[bracketLength]->winner); // hopefully it adds the node without a competitor to the end of the nextBracket vector
            m_root = bracket[bracketLength]->winner;
            m_root -> m_right = bracket[bracketLength];
        }
    }
    if(nextBracket.size() != 1){
        doubleBracketBattleWinnerHelper(nextBracket); // recursive
    }
}



template <typename T>
void TournamentTree<T>::doubleBracketBattleLoserHelper(std::vector<TournamentNode<T>*> bracket){ // same idea as bracket battle but just alters a different root that is specific for the loser tree
    std::vector<TournamentNode<T>*> nextBracket;
    for (int i = 0; i < bracket.size() - 1; i += 2){
        int val = bracket[i]->m_data->compare(bracket[i+1]->m_data);
        if (val < 0){
            bracket[i]->winner = new TournamentNode<T>(*bracket[i + 1]);
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i + 1]->winner);
            m_loser_root = bracket[i]->winner;
            m_loser_root -> m_left = bracket[i];
            m_loser_root -> m_right = bracket[i + 1];
        } else if (val > 0){
            bracket[i]->winner = new TournamentNode<T>(*bracket[i]);
            bracket[i + 1]->winner = bracket[i]->winner;
            nextBracket.push_back(bracket[i]->winner);
            m_loser_root = bracket[i]->winner;
            m_loser_root -> m_left = bracket[i];
            m_loser_root -> m_right = bracket[i + 1];
        } else {
            std::cout << "bracket index " << i << " and " << i + 1 << " are equal, the val made was: " << val << endl;
        }
        if(bracket.size() % 2 == 1 && i + 1 == bracket.size() - 2){ // checks if this is the last iteration of the loop to add the value at the end of the nextBracket vector
            int bracketLength = bracket.size() - 1;
            bracket[bracketLength]->winner = new TournamentNode<T>(*bracket[bracketLength]);
            nextBracket.push_back(bracket[bracketLength]->winner); // hopefully it adds the node without a competitor to the end of the nextBracket vector
            m_loser_root = bracket[bracketLength]->winner;
            m_loser_root -> m_right = bracket[bracketLength];
        }
    }
    if(bracket.size() != 1){
        doubleBracketBattleLoserHelper(nextBracket);
    }
}

/*
You will use these methods in your code to save your winner and/ or loser bracket trees as DOT files
Then, you'll be able to visualize your trees at this link: https://dreampuf.github.io/GraphvizOnline/
*/

// Function to save the tree as a DOT file
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for DOT output: " << filename << "\n";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(rootNode, file, nodeID);
    file << "}\n";
    file.close();
}

// Recursive helper function for DOT file generation
template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) {
    if (node == NULL) return;

    int currentID = nodeID++;

    file << "    node" << currentID << " [label=\"" << node->getMonster()->name
        << " (Power: " << node->getMonster()->screamPower << ")\"];\n";

    if (node->m_left) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->m_left, file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->m_right) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->m_right, file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
}



// ITERATIVE CONTAINS (returns true or false whether data d is found in tree)
// do any nodes in the tree contain data == d?
template <typename T>
bool TournamentTree<T>::iterContains(T d){
    if(m_root == NULL){ // tree is empty, d is not here 
        return false;
    }
    if(m_root -> m_data == d){ // root has data == d 
        return true;
    }

    // look for d elsewhere
    bool found = false; 
    TournamentNode<T>* current = m_root;

    while (!found){
        //check: should we go left or right?
        if (d > current -> m_data){ // right of current 
            current = current -> m_right;
        } else { // go left of current
            current = current -> m_left; 
        }
        // is the current node null? 
        if (current == NULL){
            // the data d is not in our tree 
            found = false; 
            break;
        }
        // does the current node have our data d?
        if (current -> m_data == d){
            found = true; 
            break;
        }
    }
    return found;
}

// RECURSIVE COINTAINS 
template <typename T>
bool TournamentTree<T>::contains(T d){ // public interface 
    return containsHelper(m_root, d);
}

template <typename T>
bool TournamentTree<T>::containsHelper(TournamentNode<T>* n, T d){ // the actual logic 
    if (n == NULL){ // finished looking thru tree and d was not found
        return false; 
    } 
    if (n -> m_data == d){ // current node n has the data d 
        return true;
    }
    if (d > n -> m_data){ // go right
        return containsHelper(n -> m_right, d);
    } else { // go left
        return containsHelper(n -> m_left, d);
    }
}

// PRINT ELEMENTS IN ORDER LEAST TO GREATEST 
template <typename T>
void TournamentTree<T>::printInOrder(){
    printIOHelper(m_root);
}

template <typename T>
void TournamentTree<T>::printIOHelper(TournamentNode<T>* n){
    if (n != NULL){
        printIOHelper(n -> m_left);
        std::cout << n -> m_data << std::endl;
        printIOHelper(n -> m_right);
    }
}


// PRINT ELEMENTS IN POST ORDER (deepest subtree left, deepest subtree right to root)
template <typename T>
void TournamentTree<T>::printPostOrder(){
    printPOHelper(m_root);
}

template <typename T>
void TournamentTree<T>::printPOHelper(TournamentNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printPOHelper(subTreeRoot->m_left);
        printPOHelper(subTreeRoot->m_right);
        cout << subTreeRoot->m_data << endl;
    }
}


// INSERT
template <typename T>
void TournamentTree<T>::insert(T d){
    insertHelper(m_root, d);
    ++m_size;
}

template <typename T>
void TournamentTree<T>::insertHelper(TournamentNode<T>*& n, T& d){ // accessing the node & data directly 
    if (n == NULL){ 
        n = new TournamentNode<T>(d);
    } else if (d > n -> m_data){
        insertHelper(n->m_right, d);
    } else {
        insertHelper(n->m_left, d);
    }
}

// GET MAX VALUE IN TREE: where would it be?
template <typename T>
T TournamentTree<T>::max(){
    return getMaxHelper(m_root);
}

template <typename T>
T TournamentTree<T>::getMaxHelper(TournamentNode<T>* n){
    if (n -> m_right == NULL){ // can't go further right, this is the max
        return n -> m_data;
    } else {
        return getMaxHelper(n -> m_right);
    }
}

// GET MIN VALUE IN TREE: where would it be?
template <typename T>
T TournamentTree<T>::min(){
    return getMinHelper(m_root);
}
template <typename T>
T TournamentTree<T>::getMinHelper(TournamentNode<T>* n){
    if (n -> m_left == NULL){ // can't go further right, this is the max
        return n -> m_data;
    } else {
        return getMinHelper(n -> m_left);
    }
}

// NAIVE MEDIAN: only works if tree is full (balanced)
template <typename T>
T TournamentTree<T>::naiveMedian(){
    return m_root -> m_data;
}


template <typename T>
void TournamentTree<T>::findTarget (T key, TournamentNode<T>*& target, TournamentNode<T>*& parent){
    // find node we want to delete and its parent 
    while (target != NULL && target -> m_data != key){
        // we haven't found target yet
        // set parent = to the current target 
        parent = target; 
        // set target to either left or right child of current target
        if (key <= target -> m_data){
            target = target -> m_left;
        } else {
            target = target -> m_right;
        }
    }
}
template <typename T>
TournamentNode<T>* TournamentTree<T>::getSuccessor (TournamentNode<T>* rightChild){
    while (rightChild -> m_left != NULL){
        rightChild = rightChild -> m_left;
    }
    return rightChild; // is the successor of target, target's rightChild's left most child
}


template <typename T>
void TournamentTree<T>::remove(T key){
    // TO DO: check that tree is not empty
    // assume tree is not empty from here on:

    TournamentNode<T>* target = NULL; 
    TournamentNode<T>* parent = NULL;

    target = m_root;

    // find actual target and parent 
    findTarget(key, target, parent); 

    if (target == NULL){
        // The key does not exist in our tree 
        return; // exit method 
    }

    // SCENARIO 1: target has 0 childrent / target is a leaf
    if (target -> m_left == NULL && target -> m_right == NULL){
        if (target == m_root){ // the tree consists of one node and we want to delete it
            m_root = NULL;
        } else { 
            if (target == parent -> m_left){ // target is the left child of parent 
                parent -> m_left = NULL;
            } else { // target is the right child of parent 
                parent -> m_right = NULL;
            }
        }
        delete target; 
        --m_size;
    }

    // SCENARIO 3: target has 2 children 
    else if (target -> m_left != NULL && target -> m_right != NULL){
        // find the successor to replace target
        TournamentNode<T>* succ = getSuccessor(target -> m_right);
        T value = succ -> m_data; 
        remove(value); // calls scenario 1 or 2 
        target -> m_data = value;
    }
    // SCENARIO 2: target has 1 child 
    else {
        TournamentNode<T>* child; 
        // check whether target has a left or right child 
        if (target -> m_left != NULL){ // target has a left child
            child = target -> m_left;
        } else { // target has a right child 
            child = target -> m_right;
        }

        if (target == m_root){
            m_root = child;
        } else {
            if(target == parent -> m_left){ // target is a left child
                parent -> m_left = child; // making the parent's left child the target's child 
            } else {
                parent -> m_right = child;
            }
        }

        target -> m_left = NULL; 
        target -> m_right = NULL; 
        delete target; 
        --m_size;
    }
}


template <typename T>
int TournamentTree<T>::maxDepthHelper(TournamentNode<T>* subRoot){
    if (subRoot == NULL){
        return 0; // base case
    }
    int leftDepth = maxDepthHelper(subRoot -> m_left);
    int rightDepth = maxDepthHelper(subRoot -> m_right);

    return std::max(leftDepth, rightDepth) + 1;
}

template <typename T>
int TournamentTree<T>::maxDepth(){
    return maxDepthHelper(m_root);
}


#endif