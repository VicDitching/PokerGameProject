#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include <iostream>
#include "Player.h"
using namespace std;

class PokerPlayer : public Player{
    private: 
        int total; 
        int chips; 
    
    public: 
        PokerPlayer(const string& name, int initialChips = 1000); 
        ~PokerPlayer(); 

        void addWinnings(int amount); 
        int getTotalWinnings() const; 
        
        void addChips(int amount); 
        int getChips() const; 
        
        void displayHand() const override; 
}; 

#endif
