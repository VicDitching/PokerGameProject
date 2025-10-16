#include <iostream>
#include "Card.h"
using namespace std;

Card::Card(string r, string s){
    rank = r; 
    suit = s; 
}

void Card::displayCard(){ cout<<rank<<" of "<<suit<<endl; }

string Card::getRank() const{ return rank; }
string Card::getSuit() const{ return suit; }