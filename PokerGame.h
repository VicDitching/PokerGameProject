#ifndef POKERGAME_H
#define POKERGAME_H

#include <iostream>
#include <fstream>
#include "Deck.h"
#include "PokerPlayer.h"

class PokerGame{
    protected: 
        Deck cards; 
        PokerPlayer user; 
        PokerPlayer computer; 
        Card community[5]; 
        int pot; 
        int initialBet; 
        
        ofstream resultsFile; 
        
    public:
        PokerGame(const string& name, int startingChips);
    
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