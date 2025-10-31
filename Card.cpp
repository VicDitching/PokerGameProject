#include <iostream>
#include "Card.h"
using namespace std;
// initializes card's rank and suit as blank 
Card::Card() : rank(""), suit("") {}
// initializes card's rank and suit
Card::Card(string r, string s){
    rank = r; 
    suit = s; 
}
// returns the rank of the card 
string Card::getRank() const{ return rank; }
// returns the suit of the card 
string Card::getSuit() const{ return suit; }
//overloaded operator 
ostream& operator<<(ostream& os, const Card& card){
    os << card.rank << " of "<<card.suit; 
    return os; 
}
