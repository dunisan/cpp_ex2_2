/*
    Player.cpp defines the player of the game.
    The player of a game has a name, a stack size, how many cardes taken.
    Note, that player can enter one game at a time. 
*/

#include "player.hpp"

using namespace ariel; 


string Player::getName()
{
    return this->_name; 
}


int Player::stacksize() {
    return this->stack_size;
}

void Player::initStackSize(){
    this->stack_size = 26;
}
void Player::reduceStackSize()
{
    this->stack_size -= 1; 
}


int Player::cardesTaken() {
    return this->cardes_taken;
}

void Player::setCardesTaken(int carde_taken)
{
    this->cardes_taken += carde_taken; 
}



bool Player::isPlaying()
{
    return this->is_playing; 
}

void Player::isPlaying(bool is_playing)
{
    this->is_playing = is_playing; 
}
