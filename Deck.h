#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "Card.h"
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;
// creates a class for Deck 
class Deck{
    private: 
        string suits[4] = {"Hearts", "Diamonds", "Clubs", "Clovers"}; 
        string ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}; 
        Card deck[52]; 
        int topIndex; 
    public:
        // function prototypes 
        void initializeDeck(); 
        void shuffleDeck(); 
        Card giveCard(); 
        int getRankValue(string rank); 
        void sortRanks(int hand[5]); 
        void countRanks(Card hand[5], int counts[13]); 
        // determines the type of hand that the user has 
        bool royalFlush(Card hand[5]); 
        bool straight(Card hand[5]);
        bool flush(Card hand[5]);
        bool straightFlush(Card hand[5]);
        bool fourKind(Card hand[5]); 
        bool fullHouse(Card hand[5]); 
        bool threeKind(Card hand[5]); 
        bool twoPair(Card hand[5]); 
        bool onePair(Card hand[5]); 
        // checks the value of the hand 
        int handEvaluator(Card hand[5]); 
};

#endif
