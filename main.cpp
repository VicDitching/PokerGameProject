#include <iostream>
#include "PokerGame.h"
using namespace std; 
int main()
{
    string name; 
    int startingChips; 
    
    cout<<"Enter your name: "; 
    getline(cin, name); 
    
    do{
        cout<<"Enter the number of chips to start with: "; 
        cin>>startingChips; 
        
        if(startingChips <= 0){
            cout<<"Error. Please enter a valid number of chips."<<endl; 
        }
    } while(startingChips <= 0); 
    
    PokerGame game(name, startingChips); 
    game.playGame(); 
    
    cout<<"Session has ended. Please check 'poker_results.txt' for saved results"<<endl; 

    return 0;
}