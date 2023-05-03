//Menu_hpp
#ifndef Menu_hpp
#define Menu_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.hpp"

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


        static Menu* s_Instance;
};
#endif //Menu_hpp