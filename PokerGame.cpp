#include "PokerGame.h"
#include <iostream>
#include <climits>
using namespace std; 

PokerGame::PokerGame(const string& name, int startingChips)
    : user(name, startingChips), computer("Computer", startingChips), pot(0) {}

void PokerGame::dealHoleCards(){
    for(int x = 0; x < 2; x++){
        user.setCard(x, cards.giveCard()); 
        computer.setCard(x, cards.giveCard()); 
    }
}

void PokerGame::dealFlop(){
    cout<<"Dealing Flop Card: "<<endl; 
    for(int x = 0; x < 3; x++){
        community[x] = cards.giveCard(); 
    }
}

void PokerGame::dealTurn() { 
    cout<<"Dealing Turn Card: "<<endl; 
    community[3] = cards.giveCard(); 
}

void PokerGame::dealRiver() {
    cout<<"Dealing River Card: "<<endl; 
    community[4] = cards.giveCard(); 
}

int PokerGame::bestFiveCardHandValues(Deck& cards, Card* all){
    int best = 0; 
    for(int x = 0; x < 7; x++){
        for(int y = x+1; y < 7; y++){
            Card hand[5]; 
            int index = 0; 
            
            for(int z = 0; z < 7; z++){
                if(z != x && z != y){
                    hand[index++] = all[z]; 
                }
            }
            
            int score = cards.handEvaluator(hand); 
            if(score > best){
                best = score; 
            }
        }
    }
    return best; 
}
        
void PokerGame::displayCommunity(int count) const{
    cout<<"===== Community Cards ====="<<endl; 
    for(int x =0; x < count; x++){
        cout<<community[x]<<endl;
    }
    cout<<endl; 
}

void PokerGame::playerTurn(bool& userFold, int& userBet){
    string choice; 
    int amount; 
    cout<<endl<<"Your hole cards ====="<<endl;
    user.displayHand(); 
    do{
        cout<<user.getName()<<", Choose action: fold, call, raise: "; 
        cin>>choice; 
        
        if(!cin || choice != "fold" && choice != "call" && choice != "raise"){
            cout<<"Error. please input a valid action."<<endl; 
            cin.clear(); 
            cin.ignore(1000, '\n');
        }
    
    }while(!cin || choice != "fold" && choice != "call" && choice != "raise" );
    
    if(choice == "fold"){
        userFold = true;
        cout<<"You fold"<<endl; 
    } else if(choice == "call"){
        userBet = initialBet; 
        user.addChips(-userBet); 
        pot+=initialBet; 
    }else if(choice == "raise"){
        cout<<"Enter raise amount: "; 
        cin>>amount;
        userBet = initialBet+amount; 
        user.addChips(-userBet); 
        pot+=userBet; 
        initialBet += userBet; 
    }
}

void PokerGame::computerTurn(bool& computerFold, int& computerBet){
    int decision = rand() % 100; 
    if(decision < 20){
        computerFold = true;
        cout<<"Computer folds"<<endl<<endl; 
    } else {
        computerBet = initialBet; 
        computer.addChips(-computerBet); 
        pot += computerBet; 
        cout<<"Computer calls"<<endl<<endl; 
    }
}
        
int PokerGame::evaluateBestHand(PokerPlayer& player){
    Card all[7]; 
    all[0] = player.getHand()[0]; 
    all[1] = player.getHand()[1]; 
    for(int x = 0; x  <5; x++){
        all[x+2] = community[x]; 
    }
    return bestFiveCardHandValues(cards, all); 
}

void PokerGame::determineWinner(bool userFold, bool computerFold, int userBet, int computerBet){
    cout<<endl<<"===== Showdown ====="<<endl; 
    if(userFold && !computerFold){
        cout<<"Computer wins the pot of "<<pot<<" chips"<<endl; 
        computer.addChips(pot);  
        computer.addWinnings(pot); 
        saveResultToFile("Computer wins by fold."); 
    } else if(computerFold && !userFold){
        cout<<user.getName()<<" wins the pot of "<<pot<<" chips"<<endl; 
        user.addChips(pot); 
        user.addWinnings(pot); 
        saveResultToFile(user.getName()+" wins by fold."); 
    } else {
        int userScore = evaluateBestHand(user); 
        int computerScore = evaluateBestHand(computer); 
        
        cout<<endl<<user.getName()<<"'s Hand: "<<endl; 
        user.displayHand(); 
        cout<<"Computer's Hand: "<<endl; 
        computer.displayHand(); 
        
        if(userScore > computerScore){
            cout<<user.getName()<<" wins the pot of "<<pot<<" chips"<<endl; 
            user.addChips(pot); 
            user.addWinnings(pot); 
            saveResultToFile(user.getName()+" wins with the better hand."); 
        }else if(computerScore > userScore){
            cout<<"Computer wins the pot of "<<pot<<" chips"<<endl; 
            computer.addChips(pot); 
            computer.addWinnings(pot); 
            saveResultToFile("Computer wins with the better hand.");
        } else {
            cout<<"It's a tie! Pot is split."<<endl; 
            user.addChips(pot/2);
            user.addWinnings(pot/2); 
            computer.addChips(pot/2); 
            user.addWinnings(pot/2); 
            saveResultToFile("Tie.");
        }
    }
}
void PokerGame::saveResultToFile(const string& result){
    ofstream file("poker_results.txt", ios::app); 
    file << user.getName() <<" vs Computer: "<< result <<endl; 
    file.close(); 
}

void PokerGame::playGame(){
    char choice; 
    bool userFold = false, computerFold = false; 
    int userBet = 0, computerBet = 0; 
    pot = 0; 
    initialBet = 10;
    initialChips = user.getChips();
    
    while(user.getChips() > 0 && computer.getChips() > 0){
        cards.initializeDeck(); 
        cards.shuffleDeck(); 
        
        dealHoleCards(); 
        playerTurn(userFold, userBet); 
        cout<<endl; 
        computerTurn(computerFold, computerBet);
        
        if(userFold||computerFold){
            determineWinner(userFold, computerFold, userBet, computerBet); 
            cout<<endl<<"Want to play another round? (y/n): "; 
            cin>>choice; 
            if(choice != 'y' && choice != 'Y') { break; }
            continue; 
        }
        
        dealFlop(); 
        displayCommunity(3); 
        playerTurn(userFold, userBet); 
        cout<<endl;
        computerTurn(computerFold, computerBet); 
        if(userFold || computerFold){
            determineWinner(userFold, computerFold, userBet, computerBet); 
            cout<<endl<<"Want to play another round? (y/n): "; 
            cin>>choice; 
            if(choice != 'y' && choice != 'Y') { break; } 
            continue;
        }
        
        dealTurn(); 
        displayCommunity(4); 
        playerTurn(userFold, userBet); 
        cout<<endl;
        computerTurn(computerFold, computerBet); 
        if(userFold || computerFold){
            determineWinner(userFold, computerFold, userBet, computerBet); 
            cout<<endl<<"Want to play another round? (y/n): "; 
            cin>>choice; 
            if(choice != 'y' && choice != 'Y') { break; }
            continue;
        }
        
        dealRiver(); 
        displayCommunity(5); 
        playerTurn(userFold, userBet); 
        cout<<endl;
        computerTurn(computerFold, computerBet);
        determineWinner(userFold, computerFold, userBet, computerBet); 
        
        cout<<endl<<"Want to play another round? (y/n): "; 
        cin>>choice; 
        if(choice != 'y' && choice != 'Y') { break; }
    }
    
    cout<<"Session has ended!"<<endl<<"Final chips: "<<endl; 
    cout<<user.getName()<<": "<<user.getChips()<<endl; 
    cout<<computer.getName()<<": "<<computer.getChips()<<endl;
    cout<<"Profit: "<<user.getTotalWinnings()-initialChips<<endl; 
}
        
