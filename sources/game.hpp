#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>

#include "player.hpp"
#include "card.hpp"


using namespace std;


namespace ariel{

    class Game{

        private: 
            Player& player1;
            Player& player2; 
            vector<Card> player_1_deck; 
            vector<Card> player_2_deck; 

            vector<string> GameLogger; 
            int win1; 
            int win2; 
            int draws; 
            int turns; 

            bool game_is_on; 

        public:

            Game(Player& player1, Player& player2):player1(player1), player2(player2) {

                if (player1.isPlaying()){
                    __throw_invalid_argument ("Player one is current playing in other game"); 
                }
                
                if(player2.isPlaying()){
                    throw invalid_argument("Player two is current playing in othe game"); 
                }
                
                
                
                player1.initStackSize();
                player2.initStackSize();
                deal_cards(); 
                player1.isPlaying(true); 
                player2.isPlaying(true);
                game_is_on = true; 
                win1 = 0;
                win2 = 0; 
                turns = 0;
                draws = 0; 
            }

            void deal_cards();
            void init_deck(vector<Card>&); 
            void shuffle(vector<Card>&);
            void deal(vector<Card>&);
            void print_deck(const vector<Card>& deck);
            Card pop_top_of_deck(vector<Card>& deck);
            void loggerUpdate(Card player1, Card player2, int winner);
            void playTurn(); 
            void playTurn(int);
            void printLastTurn();
            void playAll();
            void printWiner(); 
            void printLog(); 
            void printStats(); 

            void setWinner(Player player); 
            Player getWinner(); 


        
    };

}