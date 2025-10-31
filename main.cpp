#include <iostream>
#include "PokerGame.h"
using namespace std; 
int main()
{
    string name; 
    int startingChips; 
    // prompts user for their name 
    cout<<"Enter your name: "; 
    getline(cin, name); 
    // prompts user for number of chips that they want to start with 
    // includes error handling 
    do{
        cout<<"Enter the number of chips to start with: "; 
        cin>>startingChips; 
        
        if(startingChips <= 0 || !cin){
            cout<<"Error. Please enter a valid number of chips."<<endl; 
            cin.clear(); 
            cin.ignore(1000, '\n');
        }
    } while(startingChips <= 0 || !cin); 
    // initalizes and plays game for user 
    PokerGame game(name, startingChips); 
    game.playGame(); 
    // tells user that their rounds have been recorded onto a text file 
    cout<<"Session has ended. Please check 'poker_results.txt' for saved results"<<endl; 
    
    return 0;
}
