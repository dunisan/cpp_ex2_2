#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


using namespace std;

namespace ariel{

    class Player{
    
        private:
    
            string _name;  
    
            int stack_size;     
            int cardes_taken; 
    
            bool is_playing; 
           

        public: 

            // constructors 
            // Constructor 
            Player(const string& name): _name(name), stack_size(0), cardes_taken
            (0), is_playing(false){}

            void initStackSize();

            // getters and setters 
            int stacksize();
            void reduceStackSize(); 

            int cardesTaken(); 
            void setCardesTaken(int cardesTaken);
            
            string getName();

            bool isPlaying(); 
            void isPlaying(bool is_playing); 
   
    };

}