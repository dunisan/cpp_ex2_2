/*
    game.cpp defines the war game.
    
    Every game is played by 2 participants. 
    Every player start the game with 26 cards. 
    
    At each turn, the players put down the first card on the top of the deck, 
    and the player the has the bigger card - takes 2 of the cards to him. 
    **NOTE that Ace beats all of the cardes, except '2' the beats him. 
    
    If their is a draw, so each player puts down 2 cards, one downwards, and then one 
    upwards. The player who wins - takes all of the card to him.
    **NOTE if the last turn ends with a draw, every play takes back the cardes he put down.

    The winner is the player that has the most cards at the end of the game. 
    **NOTE only one round is played. 

    game.cpp has the needed function for implementing the game, and
    has function that keep track of the stats of the game. 
*/

#include "game.hpp"

using namespace ariel;



void Game::deal_cards(){

    vector<Card> deck; 

    init_deck(deck); 
    shuffle(deck); 
    deal(deck); 

}

void Game::init_deck(vector<Card>& deck){

    for (int s = CLUBS; s <= SPADES; s++) {
            for (int r = TWO; r <= ACE; r++) {
                deck.push_back(Card(static_cast<Rank>(r), static_cast<Suit>(s)));
            }
    }

}

void Game::shuffle(vector<Card>& deck){
    random_device rd;
    mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

void Game::deal(vector<Card>& deck){
    this->player_1_deck.clear();
    this->player_2_deck.clear();
    for (int i = 0; i < 26; i++) {
        this->player_1_deck.push_back(deck[static_cast<std::vector<Card>::size_type>(i) * 2]);
        this->player_2_deck.push_back(deck[static_cast<std::vector<Card>::size_type>(i) * 2 + 1]);
    }
}

void Game::print_deck(const vector<Card>& deck) {
    int i =0; 
    for (const auto& card : deck) {
        std::cout << i++ << "   " << card.toString() << std::endl;
    }
}

Card Game::pop_top_of_deck(vector<Card>& deck){
   
    Card top = deck.front();
    deck.erase(deck.begin());
    return top; 
}

void Game::playTurn(){

    if(!game_is_on || player1.getName() == player2.getName()){
        throw invalid_argument(" ");
    }

    this->turns++;     

    playTurn(1); 
    return; 
}

void Game::playTurn(int i){

    
    Card player1card = pop_top_of_deck(player_1_deck);
    player1.reduceStackSize();
 
    Card player2card = pop_top_of_deck(player_2_deck);
    player2.reduceStackSize();


    int player1cardvalue = player1card.getValue();
    int player2cardvalue = player2card.getValue();

    if(player1.stacksize() == 0){
        
        game_is_on = false; 

        if(player1cardvalue == player2cardvalue){
            
            this->draws++; 
            player1.setCardesTaken(i); 
            player2.setCardesTaken(i);
            
            loggerUpdate(player1card, player2card , 0); 
            return; 
        }
    }

    if(player1cardvalue == 14 && player2cardvalue ==2){
        player2.setCardesTaken(2*i);
        this->win2++; 
        loggerUpdate(player1card, player2card , 2); 
        return; 
    }

    if(player1cardvalue == 2 && player2cardvalue == 14){
        player1.setCardesTaken(2*i);
        this->win1++; 
        loggerUpdate(player1card, player2card , 1); 
        return; 
    }
    
    if(player1cardvalue > player2cardvalue){
        player1.setCardesTaken(2*i); 
        this->win1++; 
        loggerUpdate(player1card, player2card , 1); 
        return; 
    }  

    else if(player1cardvalue < player2cardvalue){
        player2.setCardesTaken(2*i);
        this->win2++; 
        loggerUpdate(player1card, player2card , 2); 
        return; 
    }

    else{ 
        this->draws++; 
        pop_top_of_deck(player_1_deck); 
        player1.reduceStackSize();

        if(player1.stacksize()==0){
            game_is_on = false; 

            player1.setCardesTaken(i+1);
            player2.setCardesTaken(i+1);

        }

        pop_top_of_deck(player_2_deck); 
        player2.reduceStackSize();

        i+=2; 
        loggerUpdate(player1card, player2card , 0);
        
        playTurn(i); 
    }

}

void Game::loggerUpdate(Card card1, Card card2, int winner){
    
    string player1name = player1.getName(); 
    string player2name = player2.getName(); 


    string roundLog = player1name + " played " + card1.toString() + " and " + player2name +" played " + card2.toString() + ", ";
    
    if (winner == 1) {
            roundLog += player1name + " wins the round!";
    } else if (winner == 2) {
            roundLog += player2name + " wins the round!";
    } else {
            roundLog += "It's a tie!"; 
    }
    GameLogger.push_back(roundLog);
}

void Game::printLastTurn()
{
    if (!GameLogger.empty()) {
        string lastTurn = GameLogger.back();
        cout << "Last turn: " << lastTurn << std::endl;
    }   
}

void Game::playAll()
{
    while(game_is_on){
        playTurn();
    }
}

void Game::printWiner(){
    if(player1.cardesTaken() > player2.cardesTaken()){
        cout << "The winner of the game is player1:" << player1.getName() << endl; 
    }
    else if (player1.cardesTaken() < player2.cardesTaken()){
        cout << "The winner of the game is player2: " << player2.getName() << endl;
    }
    else{
        cout << "It's a tie!!";
    }
}

void Game::printLog(){
    for (vector<std::string>::size_type i = 0; i < GameLogger.size(); i++) {
        string turn = GameLogger[i];
        cout << "Turn number " << i+1 << ": " << turn << endl; 
    }
}


void Game ::printStats()
{
    cout << endl << endl; 
    cout << "===================================================" << endl; 
    cout << "================   stats of game   ================" << endl; 
    cout << "===================================================" << endl; 
    cout << "wins: " << endl << player1.getName() << ":   " << this->win1 << endl  
         << player2.getName() << ":   " << this->win2 << endl;
    cout << "--------------------------------------------------" << endl; 
    cout << "wins rate: " << endl << player1.getName() << ":   " 
         << ((float)(this->win1) / (this->turns)) << endl << player2.getName() << ":   " 
         << ((float)(this->win2) / (this->turns)) << endl; 
    cout << "--------------------------------------------------" << endl; 
    cout << "draws:  "  << this->draws << endl; 
    cout << "--------------------------------------------------" << endl; 
    cout << "cards taken:" << endl << player1.getName() << ":   " << player1.cardesTaken()
         << endl << player2.getName() << ":  " << player2.cardesTaken() << endl;
    cout << "==================================================" << endl; 

}



