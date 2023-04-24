#include "card.hpp"


using namespace ariel; 

string Card::toString() const{

    string rankStr, suitStr;
    
    switch(rank) {
        
        case TWO: rankStr = "2"; break;
        case THREE: rankStr = "3"; break;
        case FOUR: rankStr = "4"; break;
        case FIVE: rankStr = "5"; break;
        case SIX: rankStr = "6"; break;
        case SEVEN: rankStr = "7"; break;
        case EIGHT: rankStr = "8"; break;
        case NINE: rankStr = "9"; break;
        case TEN: rankStr = "10"; break;
        case JACK: rankStr = "Jack"; break;
        case QUEEN: rankStr = "Queen"; break;
        case KING: rankStr = "King"; break;
        case ACE: rankStr = "Ace"; break;
    }
    switch(suit) {
        case CLUBS: suitStr = "Clubs"; break;
        case DIAMONDS: suitStr = "Diamonds"; break;
        case HEARTS: suitStr = "Hearts"; break;
        case SPADES: suitStr = "Spades"; break;
    }
    return rankStr + " of " + suitStr;
}

int Card::getValue() {
    return rank;
}
        

