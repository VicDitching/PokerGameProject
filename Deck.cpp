#include "Deck.h"
// initializes the deck with their rank and suit 
void Deck::initializeDeck(){
    int index = 0; 
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 13; y++){
            deck[index] = Card(ranks[y], suits[x]);
            index++; 
        }
    }
}
// shuffles the deck
// uses the algorithm library 
void Deck::shuffleDeck(){
    random_device rd; 
    mt19937 g(rd()); 
    shuffle(deck, deck+52, g); 
}
// returns a card 
Card Deck::giveCard(){
    return deck[topIndex++];
}
// returns the value of the rank 
int Deck::getRankValue(string rank){
    for(int x = 0; x < 13; x++){
        if(ranks[x] == rank){
            return x; 
        }
    }
    return -1; 
}
// sorts the ranks in user's hand 
void Deck::sortRanks(int hand[5]){
    for(int x = 0; x < 4; x++){
        for(int y = x + 1; y < 5; y++){
            if(hand[x] < hand[y]){
                swap(hand[x], hand[y]); 
            }
        }
    }
}
// counts the value of the ranks in hand
void Deck::countRanks(Card hand[5], int counts[13]){
    for(int x = 0; x < 13; x++){ counts[x] = 0; }
    for(int y = 0; y < 5; y++){
        int val= getRankValue(hand[y].getRank()); 
        counts[val]++; 
    }
}
// returns true if hand was a royal flush 
bool Deck::royalFlush(Card hand[5]){
    string suit = hand[0].getSuit();
    for(int x = 1; x < 5; x++){
        if(hand[x].getSuit() != suit){ return false; }
    }
    int values[5]; 
    for(int y = 0; y < 5; y++){ values[y] = getRankValue(hand[y].getRank()); }
    int royals[5] = {8, 9, 10, 11, 12}; 
    for(int z = 0; z < 5; z++){
        if(values[z] != royals[z]){ return false; }
    }
    return true;
}
// return true if hand is a straight 
bool Deck::straight(Card hand[5]){
    int values[5]; 
    for(int x = 0; x < 5; x++){
        values[x] = getRankValue(hand[x].getRank()); 
    }
    sortRanks(values); 
    
    if(values[4] == 12 && values[0] == 0 && values[1] == 1 && values[2] == 2 && values[3] ==3){
        return true; 
    }
    for(int y = 0; y < 4; y++){
        if(values[y+1] != values[y] + 1){
            return false; 
        }
    }
    return true; 
}
// returns true if hand is a flush 
bool Deck:: flush(Card hand[5]){
    string suit = hand[0].getSuit(); 
    for(int x = 1; x < 5; x++){
        if(hand[x].getSuit() != suit){
            return false; 
        }
    }
    return true;
}
// returns true if hand is a straight flush 
bool Deck::straightFlush(Card hand[5]){
    return flush(hand) && straight(hand); 
}
// returns true if hand is a four of a kind 
bool Deck::fourKind(Card hand[5]){
    int counts[13];
    countRanks(hand, counts); 
    for(int x = 0; x < 13; x++){
        if(counts[x] == 4){ return true; }
    }
    return false; 
}
// returns true if hand is a full house 
bool Deck::fullHouse(Card hand[5]){
    int counts[13]; 
    countRanks(hand, counts); 
    bool three = false; 
    bool two = false;
    for(int x= 0; x < 13; x++){
        if(counts[x] == 3) { three = true; }
        else if(counts[x] == 2) { two = true; }
    }
    return three && two; 
}
// returns true if hand is a three of a kind 
bool Deck::threeKind(Card hand[5]){
    int counts[13]; 
    countRanks(hand, counts);
    for(int x = 0; x < 13; x++){
        if(counts[x] == 3){ return true; }
    }
    return false; 
}
// returns true if hand has two pairs
bool Deck::twoPair(Card hand[5]){
    int counts[13]; 
    countRanks(hand, counts); 
    int pairs = 0; 
    
    for(int x = 0; x < 13; x++){
        if(counts[x] == 2){
            pairs++; 
        }
    }
    return pairs == 2; 
}
// returns true if hand has one pair 
bool Deck::onePair(Card hand[5]){
    int counts[13]; 
    countRanks(hand, counts); 
    for(int x = 0; x < 13; x++){
        if(counts[x] == 2){
            return true; 
        }
    }
    return false; 
}
//returns a value based on hand
int Deck::handEvaluator(Card hand[5]){
    if(royalFlush(hand)){
        return 9; 
    } else if(straightFlush(hand)){
        return 8; 
    } else if(fourKind(hand)){
        return 7; 
    } else if(fullHouse(hand)){
        return 6; 
    } else if(flush(hand)){
        return 5; 
    } else if(straight(hand)){
        return 4; 
    } else if(threeKind(hand)){
        return 3; 
    } else if(twoPair(hand)){
        return 2; 
    } else if (onePair(hand)){
        return 1; 
    }
    int value; 
    for(int x = 0; x < 5; x++){
        value += getRankValue(hand[x].getRank()); 
    }
    return value; 
}
