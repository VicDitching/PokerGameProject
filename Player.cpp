#include "Player.h"
// initializes player's name
Player::Player(const string& n){
    name = n; 
    cout<<name<<" has entered the table"<<endl; 
}
// deconstructor of player
Player::~Player(){
    cout<<name<<" has left the table"<<endl; 
}
// initializes the deck of the player 
void Player::setCard(int index, const Card& c){
    if(index >= 0 && index < 5){
        hand[index] = c; 
    }
}
// returns player's hand 
Card* Player::getHand(){
    return hand;
}
// displayes the first two cards of the user 
void Player::displayHand() const{
    cout<<name<<"'s Hand: "<<endl; 
    for(int i = 0; i < 2; i++){
        cout<<hand[i]<<endl; 
    }
} 
// returns player's name 
string Player::getName() const{
    return name; 
}
