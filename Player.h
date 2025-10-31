#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Card.h"
using namespace std;
// creates a class called Player 
class Player{
    protected: 
        string name; 
        Card hand[5]; 
    
    public: 
        // constructor and deconstructor 
        Player(const string& n); 
        virtual ~Player(); 
        // function prototypes 
        void setCard(int index, const Card& c); 
        Card* getHand(); 
        virtual void displayHand() const; 
        string getName() const; 
};

#endif
