#include <iostream>
#include "Card.h"
using namespace std;

Card::Card() : rank(""), suit("") {}

Card::Card(string r, string s){
    rank = r; 
    suit = s; 
}

string Card::getRank() const{ return rank; }
string Card::getSuit() const{ return suit; }

ostream& operator(ostream& os, const Card& card){
    os << card.rank << " of " << card.suit; 
    return os; 
}
