#include "PokerGame.h"
// constructor that uses initializations 
PokerGame::PokerGame(const string& name, int startingChips)
    : user(name, startingChips), computer("Computer", startingChips), pot(0) {}
// deals the first two cards to both user and computer 
void PokerGame::dealHoleCards(){
    for(int x = 0; x < 2; x++){
        user.setCard(x, cards.giveCard()); 
        computer.setCard(x, cards.giveCard()); 
    }
}
// deals the three cards to start 
void PokerGame::dealFlop(){
    cout<<"Dealing Flop Card: "<<endl; 
    for(int x = 0; x < 3; x++){
        community[x] = cards.giveCard(); 
    }
}
// deals the fourth card 
void PokerGame::dealTurn() { 
    cout<<"Dealing Turn Card: "<<endl; 
    community[3] = cards.giveCard(); 
}
// deals the fifth card 
void PokerGame::dealRiver() {
    cout<<"Dealing River Card: "<<endl; 
    community[4] = cards.giveCard(); 
}
// calculates the highest possible hand score, the player can achieve 
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
// displays the five cards on the table 
void PokerGame::displayCommunity(int count) const{
    cout<<"===== Community Cards ====="<<endl; 
    for(int x =0; x < count; x++){
        cout<<community[x]<<endl;
    }
    cout<<endl; 
}
// creates user's turn 
void PokerGame::playerTurn(bool& userFold, int& userBet){
    string choice; 
    int amount; 
    cout<<endl<<"Your hole cards ====="<<endl;
    user.displayHand(); 
    do{
        // prompts the user's choice of action 
        cout<<user.getName()<<", Choose action: fold, check, call, raise: "; 
        cin>>choice; 
        // error handling 
        if(!cin || choice != "fold" && choice != "check" && choice != "call" && choice != "raise"){
            cout<<"Error. please input a valid action."<<endl; 
            cin.clear(); 
            cin.ignore(1000, '\n');
        }
    
    }while(!cin || choice != "fold" && choice != "check" && choice != "call" && choice != "raise" );
    
    if(choice == "fold"){ // sets true if user folds 
        userFold = true;
        cout<<"You fold"<<endl; 
    } else if(choice == "check"){ // doesn't add anything to the pot and allows user to not bet money 
        userBet = 0; 
        cout<<"You check"<<endl; 
    } 
    else if(choice == "call"){ // user adds the initial bet into pot 
        userBet = initialBet; 
        user.addChips(-userBet); 
        pot+=initialBet; 
    }else if(choice == "raise"){ // user chooses to raise amount of chips into pot 
        cout<<"Enter raise amount: "; 
        cin>>amount;
        userBet = initialBet+amount; 
        user.addChips(-userBet); 
        pot+=userBet; 
        initialBet += userBet; 
    }
}
// creates computer's turn 
void PokerGame::computerTurn(bool& computerFold, int& computerBet){
    int decision = rand() % 100; 
    if(decision < 10){ // 10 percent chance for computer to fold 
        computerFold = true;
        cout<<"Computer folds"<<endl<<endl; 
    } else { // 90 percent chance for computer to call 
        computerBet = initialBet; 
        computer.addChips(-computerBet); 
        pot += computerBet; 
        cout<<"Computer calls"<<endl<<endl; 
    }
}
// returns the score of the best hand of player 
int PokerGame::evaluateBestHand(PokerPlayer& player){
    Card all[7]; 
    all[0] = player.getHand()[0]; 
    all[1] = player.getHand()[1]; 
    for(int x = 0; x  <5; x++){
        all[x+2] = community[x]; 
    }
    return bestFiveCardHandValues(cards, all); 
}
// determine's the winner in the poker game if no one folds
void PokerGame::determineWinner(bool userFold, bool computerFold, int userBet, int computerBet){
    cout<<endl<<"===== Showdown ====="<<endl; 
    if(userFold && !computerFold){ // if user folds, computer gets pot 
        cout<<"Computer wins the pot of "<<pot<<" chips"<<endl; 
        computer.addChips(pot);  
        computer.addWinnings(pot); 
        saveResultToFile("Computer wins by fold."); 
    } else if(computerFold && !userFold){ // if computer folds, user gets pot 
        cout<<user.getName()<<" wins the pot of "<<pot<<" chips"<<endl; 
        user.addChips(pot); 
        user.addWinnings(pot); 
        saveResultToFile(user.getName()+" wins by fold."); 
    } else {
        // calculates the score's of user and computer 
        int userScore = evaluateBestHand(user); 
        int computerScore = evaluateBestHand(computer); 
        // displays both hands of user and computer 
        cout<<endl<<user.getName()<<"'s Hand: "<<endl; 
        user.displayHand(); 
        cout<<"Computer's Hand: "<<endl; 
        computer.displayHand(); 
        // if no one folds 
        if(userScore > computerScore){ // if user wins, user gets pot 
            cout<<user.getName()<<" wins the pot of "<<pot<<" chips"<<endl; 
            user.addChips(pot); 
            user.addWinnings(pot); 
            saveResultToFile(user.getName()+" wins with the better hand."); 
        }else if(computerScore > userScore){ // if computer wins, computer gets pot 
            cout<<"Computer wins the pot of "<<pot<<" chips"<<endl; 
            computer.addChips(pot); 
            computer.addWinnings(pot); 
            saveResultToFile("Computer wins with the better hand.");
        } else { // if there is a tie, user and computer gets half of the pot 
            cout<<"It's a tie! Pot is split."<<endl; 
            user.addChips(pot/2);
            user.addWinnings(pot/2); 
            computer.addChips(pot/2); 
            user.addWinnings(pot/2); 
            saveResultToFile("Tie.");
        }
    }
}
// saves results from round into text file 
void PokerGame::saveResultToFile(const string& result){
    try{
        ofstream file("poker_results.txt", ios::app); 
        if(!file.is_open()){
            throw runtime_error("Error. Unable to open file.");
        }
        file << user.getName() <<" vs Computer: "<< result <<endl; 
        file.close(); 
    } catch(const exception& e){ // catches standard exceptions 
        cerr<<"File save error: "<<e.what()<<endl; 
    } catch(...){ // catches other unknown exceptions 
        cerr<<"Unknown error during file saving."<<endl; 
    }
}
// creates the whole game of poker
// allows for user to play as many rounds as they want until runs of chips or user wants to end 
void PokerGame::playGame(){
    try{
        char choice; 
        initialChips = user.getChips();
    
        while(user.getChips() > 0 && computer.getChips() > 0){
            bool userFold = false, computerFold = false; 
            int userBet = 0, computerBet = 0; 
            pot = 0;
            initialBet = 10;
            //initializes and shuffles deck 
            cards.initializeDeck(); 
            cards.shuffleDeck(); 
            //start's first round 
            dealHoleCards(); 
            playerTurn(userFold, userBet); 
            cout<<endl; 
            if(!userFold){
                computerBet = 0; 
                cout<<"Computer checks"<<endl<<endl; 
            }
            if(userFold||computerFold){ // checks if user or computer chooses to fold 
                determineWinner(userFold, computerFold, userBet, computerBet); 
                cout<<endl<<"Want to play another round? (y/n): "; 
                cin>>choice; 
                if(choice != 'y' && choice != 'Y') { break; }
                continue; 
            }else if(user.getChips() == 0 || computer.getChips() == 0){
                break; 
            }
            // second round 
            dealFlop(); 
            displayCommunity(3); 
            playerTurn(userFold, userBet); 
            cout<<endl;
            if(!userFold){
                computerTurn(computerFold, computerBet);
            }
            if(userFold || computerFold){ // checks if user or computer chooses to fold 
                determineWinner(userFold, computerFold, userBet, computerBet); 
                cout<<endl<<"Want to play another round? (y/n): "; 
                cin>>choice; 
                if(choice != 'y' && choice != 'Y') { break; } 
                continue;
            }else if(user.getChips() == 0 || computer.getChips() == 0){
                break; 
            }
            // third round 
            dealTurn(); 
            displayCommunity(4); 
            playerTurn(userFold, userBet); 
            cout<<endl;
            if(!userFold){
                computerTurn(computerFold, computerBet);
            }
            if(userFold || computerFold){ // checks if user or computer chooses to fold 
                determineWinner(userFold, computerFold, userBet, computerBet); 
                cout<<endl<<"Want to play another round? (y/n): "; 
                cin>>choice; 
                if(choice != 'y' && choice != 'Y') { break; }
                continue;
            }else if(user.getChips() == 0 || computer.getChips() == 0){
                break; 
            }
            // fourth round 
            dealRiver(); 
            displayCommunity(5); 
            playerTurn(userFold, userBet); 
            cout<<endl;
            if(!userFold){
                computerTurn(computerFold, computerBet);
            }
            // determines the winner of the user and computer 
            determineWinner(userFold, computerFold, userBet, computerBet); 
            // prompts user if they would like to play another round 
            cout<<endl<<"Want to play another round? (y/n): "; 
            cin>>choice; 
            if(choice != 'y' && choice != 'Y') { break; }
        }
        // checks if user or computer has zero chips 
        if(user.getChips() == 0){
            cout<<user.getName()<<" has no more chips to bet!"<<endl; 
        } else if(computer.getChips() == 0){
            cout<<"Computer had no more chips to bet!"<<endl; 
        }
        // shows that the session has ended and shows user's and computer's chips 
        cout<<"Session has ended!"<<endl<<"Final chips: "<<endl; 
        cout<<user.getName()<<": "<<user.getChips()<<endl; 
        cout<<computer.getName()<<": "<<computer.getChips()<<endl;
        // shows the profit user has gained or lost 
        cout<<"Profit: "<<user.getChips()-initialChips<<endl; 
    } catch (const exception& e){ // catches standard exceptions 
        cerr<<"A critical runtime error occured durng game execution: "<<e.what()<<endl; 
    } catch (...){ // catches any other unknown exceptions 
        cerr<<"An unknown and unhandled fatal error occured."<<endl; 
    }
}
        
