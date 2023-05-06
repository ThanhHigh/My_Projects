
#include "Engine.hpp"
#include "Timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>



int main(int argc, char* args[])
{
    std::srand(time(NULL));
    Engine::GetInstance()->initGame();
    while (Engine::GetInstance()->isRunningGame())
    {
        Engine::GetInstance()->eventsGame();
        // Ban dầu là ntn
        Engine::GetInstance()->updateGame();
        Engine::GetInstance()->renderGame();
        Timer::GetInstance()->timerTicks();
    }

    Engine::GetInstance()->clearGame();

    //Debug
    SDL_Delay(10000);
    //Debug
    return 0;
}