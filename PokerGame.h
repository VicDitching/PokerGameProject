#ifndef POKERGAME_H
#define POKERGAME_H

#include <iostream>
#include <climits>
#include <fstream>
#include "Deck.h"
#include "PokerPlayer.h"
// creates a class for Poker game 
class PokerGame{
    protected: 
        Deck cards; 
        Card community[5];
        
        PokerPlayer user;
        PokerPlayer computer; 
        
        int pot; 
        int initialBet; 
        int initialChips; 
        
        ofstream resultsFile; 
        
    public:
        // constructor 
        PokerGame(const string& name, int startingChips);
        //function prototypes 
        void dealHoleCards(); 
        void dealFlop(); 
        void dealTurn(); 
        void dealRiver();
        int bestFiveCardHandValues(Deck& deck, Card* all); 
        
        void displayCommunity(int count) const; 
        void playerTurn(bool& userFold, int& userBet); 
        void computerTurn(bool& computerFold, int& computerBet);
        
        int evaluateBestHand(PokerPlayer& player); 
        void determineWinner(bool userFold, bool computerFold, int userBet, int computerBet); 
        void saveResultToFile(const string& result); 
    
        void playGame();
};


#endif
