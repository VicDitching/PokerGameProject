#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include <iostream>
#include "Player.h"
using namespace std;
// creates a child class from Player called Poker Player 
class PokerPlayer : public Player{
    private: 
        int total; 
        int chips; 
    
    public: 
        // constructor and deconstructor 
        PokerPlayer(const string& name, int initialChips = 50); 
        ~PokerPlayer(); 
        //function prototypes 
        void addWinnings(int amount); 
        int getTotalWinnings() const; 
        void addChips(int amount); 
        int getChips() const; 
        // override function 
        void displayHand() const override; 
}; 

#endif
