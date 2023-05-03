//GameOver_hpp
#ifndef GameOver_hpp
#define GameOver_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.hpp"
#include "Warrior.hpp"

class GameOver
{
    public:
        static GameOver* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameOver();
        }
        void init();
        void render();
        void updateDeath();
        void update();
        void exit();        
        inline bool isOver(){ return over; }
        bool over;
    private:
        static GameOver* s_Instance;
        

};
#endif