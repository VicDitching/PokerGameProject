#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;
// creates class for Card 
class Card{
    private: 
        string rank; 
        string suit; 
    public: 
        // default and non-default constructors 
        Card(); 
        Card(string r, string s);
        // function prototypes 
        string getRank() const;
        string getSuit() const;
        friend ostream& operator<<(ostream& os, const Card& card); 
};

#endif
