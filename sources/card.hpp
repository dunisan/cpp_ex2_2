#pragma once




#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


using namespace std;

namespace ariel{


    enum Rank {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
    enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

    class Card{

        private:
            int rank; 
            int suit;

        public: 
            Card(Rank rank, Suit suit): rank(rank), suit(suit) {} 

        string toString() const;
        int getValue(); 



    };

}