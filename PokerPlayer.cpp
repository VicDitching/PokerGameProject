#include "PokerPlayer.h"
// constructor which uses intializations 
PokerPlayer::PokerPlayer(const string& name, int initialChips) 
    : Player(name), total(0) ,chips(initialChips) {}
// deconstructor 
PokerPlayer::~PokerPlayer() {}
// adds the winnings user has gained/losed 
void PokerPlayer::addWinnings(int amount){ total += amount; }
// returns the winnings of the user 
int PokerPlayer::getTotalWinnings() const{ return total; }
// adds the chips user has gained/losed 
void PokerPlayer::addChips(int amount){ chips += amount; }
// returns the user's chips 
int PokerPlayer::getChips() const{ return chips; }
// overrided function where it shows user's hand and chips 
void PokerPlayer::displayHand() const{
    cout<<"[PokerPlayer] " << name <<"'s Hand: "<<endl; 
    for(int x = 0; x < 2; x++){
        cout<<hand[x]<<endl;  
    }
    cout<<endl<<"Chips: "<<chips<<endl<<endl;
}
