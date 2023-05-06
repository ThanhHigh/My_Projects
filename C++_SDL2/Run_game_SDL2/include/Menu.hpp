//Menu_hpp
#ifndef Menu_hpp
#define Menu_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.hpp"

const SDL_Color MOUSEOVER_COLOR = {255, 230, 255, 255};
const SDL_Color UNMOUSE_COLOR = {180, 180, 20, 240};

class Menu
{
    public:
        static Menu* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu();
        }
        virtual bool init();
        virtual bool exit();
        virtual void update();
        virtual void render();
        bool isMenu;
        inline bool isneedMenu() { return isMenu; }

    private:
        static void startGame();
        static void setting();
        static void editor();
        static void quit();
        SDL_Color colorMenuStart = UNMOUSE_COLOR;
        SDL_Color colorMenuQuit = UNMOUSE_COLOR;
        SDL_Rect StartGame;
        SDL_Rect QuitGame;
        static Menu* s_Instance;
};
#endif //Menu_hpp