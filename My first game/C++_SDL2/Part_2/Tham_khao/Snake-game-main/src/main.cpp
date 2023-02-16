///Snake

//Game Engine
#include "Engine.h"

//Screen dimansion constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Game title
const std::string GAME_TITLE = "Snakes";

//Frame per seconds
const int FPS = 60;
const int frameDelay = 1000 / FPS;

///main
int main(int argc, char* argv[])
{
    //Initialize Game Engine
    Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE.c_str());

    //Count frametime
    Uint32 frameStart;
    int frameTime;

    //Game loop
    while (Engine::isRunning())
    {
        //Get the time that the frame started
        frameStart = SDL_GetTicks();

        //Handle Events from Player
        Engine::handleEvents();

        //Render animation
        Engine::render(); 

        //Delay time
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //Close Game Engine
    Engine::close();

    return 0;
}
