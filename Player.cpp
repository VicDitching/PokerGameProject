#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(const string& n){
    name = n; 
    cout<<name<<" has entered the table"<<endl; 
}

Player::~Player(){
    cout<<name<<" has left the table"<<endl; 
}

void Player::setCard(int index, const Card& c){
    if(index >= 0 && index < 5){
        hand[index] = c; 
    }
}

Card* Player::getHand(){
    return hand;
}

void Player::displayHand() const{
    cout<<name<<"'s Hand: "<<endl; 
    for(int i = 0; i < 2; i++){
        cout<<hand[i]<<endl; 
    }
} 

string Player::getName() const{
    return name; 
}
