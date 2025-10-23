#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card{
    private: 
        string rank; 
        string suit; 
    public: 
        Card(); 
        Card(string r, string s);
        
        string getRank() const;
        string getSuit() const;
        friend ostream& operator<<(ostream& os, const Card& card); 
};

#endif
