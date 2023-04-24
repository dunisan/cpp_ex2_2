#include <iostream>
#include <stdexcept>

#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace std;
using namespace ariel;



TEST_CASE("Initialization"){

    Player p1("Harry"); 
    Player p2("Ron"); 

    Game game(p1,p2); 

    CHECK(p1.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);

    CHECK(p2.stacksize() == 26);
    CHECK(p2.cardesTaken() == 0);

    
}


TEST_CASE("Playing game"){

    Player p1("Harry"); 
    Player p2("Ron"); 
    Player p3("Hermione");

// player in 2 games, or player 2 times in game
    Game game(p1, p2); 
    CHECK_THROWS(Game(p1,p3)); 
    CHECK_THROWS(Game(p3,p3)); 

// player stack decrease after playing turn and equals to rival stack of cards 
    game.playTurn(); 
    CHECK(p1.stacksize()<=25); 
    CHECK(p1.stacksize() == p2.stacksize());
    CHECK(p1.cardesTaken() != p2.cardesTaken()); 

    // play all game

    game.playAll();
    CHECK(p1.cardesTaken() + p2.cardesTaken() == 52);
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    
  
}



TEST_CASE("prints of game"){
    Player p1("Harry"); 
    Player p2("Ron"); 

    Game g(p1,p2); 

    // before first turn 
    CHECK_THROWS(g.printLastTurn());
    CHECK_THROWS(g.printLog());
    CHECK_THROWS(g.printStats());
    CHECK_THROWS(g.printWiner()); 
    
    // after one turn 
    g.playTurn(); 
    CHECK_NOTHROW(g.printLastTurn());
    CHECK_NOTHROW(g.printLog());
    CHECK_NOTHROW(g.printStats());
    if(p1.stacksize() != 0){
        CHECK_THROWS(g.printWiner()); 
    }

    g.playAll();
    CHECK_NOTHROW(g.printLastTurn());
    CHECK_NOTHROW(g.printLog());
    CHECK_NOTHROW(g.printStats());
    CHECK_NOTHROW(g.printWiner()); 


}


