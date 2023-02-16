//    Nguyen Duc Thanh
//    UET- 22021150
//    Temple Run 2D

//Header
#include "Engine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include <string>

//Screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Game FPS Setting
const int GAME_FPS = 60;
const int frameMDelay = 1000 / GAME_FPS;

//Game title
const std::string GAME_TITLE = "Temple Run";

int main(int argc, char* args[])
{
    //Build Game Engine
    Engine* engine = new Engine;

    Uint32 gameTime;
    int frameTime;

    while (engine->isRunning())
    {
        //Start frame rate
        gameTime = SDL_GetTicks();

        //Handle Event
        engine->handleEvent();
        
        //The game loop
        engine->loop();

        //The game render
        engine->render();

        //Handle state

        
        //End the frame
        frameTime = SDL_GetTicks() - gameTime;

        //Frame Delay
        if (frameTime < frameMDelay)
            SDL_Delay(frameMDelay - frameTime);
    }

    //Close game engine
    engine->close();

    //Delete the game engine
    delete engine;
    engine = NULL;

    return 0;   
}