
//Include Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
#include <conio.h>

#include "Engine.hpp"


//Const Variables
//Title
const std::string TITLE = "Snake Xenzia";

//Screen dimansion
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Time
const int FPS = 60;
const int frameTime = 1000 / FPS;

int main(int argc, char* argv[])
{
    Uint32 gameTime;
    int loopTime;

    Engine::init(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (Engine::isRunning())
    {
        //Take time
        gameTime = SDL_GetTicks();

        //handleEvent
        Engine::handleEvent();

        //update
        Engine::update();

        //render
        Engine::render();

        //Caculate time
        loopTime = SDL_GetTicks() - gameTime;

        if (loopTime < frameTime) 
            //Delay
            SDL_Delay(frameTime - loopTime);
    }

    //Quit game
    Engine::close();

    return 0;   
}

//g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

//g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && start bin/debug/main