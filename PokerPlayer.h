#ifndef POKERPLAYER_H
#define POKERPLAYER_H

#include <iostream>
#include "Player.h"
using namespace std;

class PokerPlayer : public Player{
    private: 
        int score; 
        int total; 
        int chips; 
        
    public: 
        PokerPlayer(const string& name, int initialChips = 1000); 
        ~PokerPlayer(); 
        
        void setScore(int s); 
        int getScore() const; 
        
        void addWinnings(int amount); 
        int getTotalWinnings() const; 
        
        void addChips(int amount); 
        void subtractChips(int amount); 
        int getChips() const; 
        
        void displayHand() const override; 
}; 

#endif