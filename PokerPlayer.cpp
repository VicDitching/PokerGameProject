#include <iostream>
#include "PokerPlayer.h"
using namespace std;

PokerPlayer::PokerPlayer(const string& name, int initialChips) 
    : Player(name), score(0), total(0) ,chips(initialChips) {}
    
PokerPlayer::~PokerPlayer() {}

void PokerPlayer::setScore(int s){
    score = s; 
}

int PokerPlayer::getScore() const{
    return score; 
}

void PokerPlayer::addWinnings(int amount){
    total += amount; 
}

int PokerPlayer::getTotalWinnings() const{
    return total; 
}

void PokerPlayer::addChips(int amount){
    chips += amount; 
}

int PokerPlayer::getChips() const{
    return chips; 
}

void PokerPlayer::displayHand() const{
    cout<<"[PokerPlayer] " << name <<"'s Hand: "<<endl; 
    for(int x = 0; x < 2; x++){
        hand[x].displayCard(); 
    }
    cout<<endl<<"Chips: "<<chips<<endl; 
    cout<<"Total Winnings: "<<total<<endl<<endl; 
}