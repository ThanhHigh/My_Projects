//SDL headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ headers
#include <iostream>

//Project headers
#include "Game.hpp"

//Dimension size window
const int WIDTH_SCREEN = 640;
const int HEIGHT_SCREEN = 480;

//Variables

//Game
Game* game = nullptr;

//Frame rate
const int FPS = 60;
const int FrameDelay = 1000 / FPS;
Uint32 FrameStart = 0;
int FrameTime;

int main(int argc, char* args[])
{
    game = new Game;

    //Initilize Game
    game -> init("Game_from_scratch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEN, HEIGHT_SCREEN, 0);

    while (game -> running())
    {
        //Time start game
        FrameStart = SDL_GetTicks();

        game -> HandleEvent();
        game -> Update();
        game -> Render();

        FrameTime = SDL_GetTicks() - FrameStart;

        if (FrameDelay > FrameTime)
            SDL_Delay(FrameDelay - FrameTime);
    }

    game -> Clean();

    return 0;
}

