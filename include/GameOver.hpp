//GameOver_hpp
#ifndef GameOver_hpp
#define GameOver_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.hpp"
#include "Warrior.hpp"

const SDL_Color MOUSEOVER_COLOUR = {255, 230, 255, 255};
const SDL_Color UNMOUSE_COLOUR = {180, 180, 20, 240};

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
        bool m_GameOver;
        bool m_PlayAgain;
        inline bool wantPlayAgain(){ return m_PlayAgain; }
        inline void setNotPlayAgain(){ m_PlayAgain = false; }
        inline bool isOver(){ return m_GameOver; }

    private:
        static GameOver* s_Instance;
        SDL_Rect PlayAgiain;
        SDL_Rect QuitGame;
        SDL_Color colorPlayAgain = UNMOUSE_COLOUR;
        SDL_Color colorQuitGame = UNMOUSE_COLOUR;
        
};
#endif