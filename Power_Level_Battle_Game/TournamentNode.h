/*
Joshua McCarthy
Ava DeCristofaro
002449270
jomccarthy@chapman.edu
CPSC350-03
PA5
*/

#ifndef TOURNAMENTNODE_H
#define TOURNAMENTNODE_H
#include <cstdlib>    // TO USE NULL
#include "Monster.h"
using namespace std;

template <typename T>
class TournamentNode{ 
    public:
        TournamentNode(T d);
        TournamentNode(TournamentNode<T>& d);
        TournamentNode(TournamentNode<T>& d, int num);
        virtual ~TournamentNode();
        T getMonster();
        string getName(){return getMonster().getMonsterName();};
        TournamentNode<T>* getLeft();
        TournamentNode<T>* getRight();
        /*
        Make BST a friend class of TreeNode

        Normally, the private and protected members of a class can only be accessed by 
        the class itself and its derived classes. 
        However, by declaring another class as a "friend," the class allows that other 
        class to access its private and protected members directly.
        */
        template <typename S>
        friend class TournamentTree;   // So, now, TournaamentTree can access private and protected stuff in TournamentNode

    private:
        T m_data;
        TournamentNode<T>* winner;
        TournamentNode<T>* m_left; 
        TournamentNode<T>* m_right;
};


template <typename T>
TournamentNode<T>::TournamentNode(T d){ // default constructor
    m_data = d;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
TournamentNode<T>::TournamentNode(TournamentNode<T>& d){ // copy constructor for winner bracket nodes
    m_data = d.m_data;
    m_left = d.m_left;
    m_right = d.m_right;
}

template <typename T>
TournamentNode<T>::TournamentNode(TournamentNode<T>& d, int num){ // copy constructor for loser bracket nodes
    m_data = d.m_data;
    m_left = NULL;
    m_right = NULL;
}


template <typename T>
TournamentNode<T>::~TournamentNode(){ // destructor
    winner = NULL;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
T TournamentNode<T>::getMonster(){ // getter method for monster's data
    return m_data;
}

template <typename T>
TournamentNode<T>* TournamentNode<T>::getLeft(){ // getter for left child
    return m_left;
}

template <typename T>
TournamentNode<T>* TournamentNode<T>::getRight(){ // getter for right child
    return m_right;
}

#endif