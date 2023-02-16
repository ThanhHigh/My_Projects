
//Include Header
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
    Engine* engine = new Engine();
    Uint32 gameTime;
    int loopTime;

    engine->init(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (engine->isRunning())
    {
        //Take time
        gameTime = SDL_GetTicks();

        //handleEvent
        engine->handleEvent();

        //update
        engine->update();

        //render
        engine->render();

        //Caculate time
        loopTime = SDL_GetTicks() - gameTime;

        if (loopTime < frameTime) 
            //Delay
            SDL_Delay(frameTime - loopTime);
    }

    //Quit game
    engine->close();

    return 0;   
}