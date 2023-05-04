//Menu_hpp
#ifndef Menu_hpp
#define Menu_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "GameState.hpp"

class Menu : public GameState
{
    public:
        Menu();
        virtual bool init();
        virtual bool exit();
        virtual void update();
        virtual void render();

    private:
        static void startGame();
        static void setting();
        static void editor();
        static void quit();
};
#endif //Menu_hpp