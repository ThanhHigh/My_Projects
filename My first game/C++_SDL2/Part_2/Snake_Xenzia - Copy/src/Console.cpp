//Console [Source]
#include "Console.hpp"

//Include header
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

//class Console
Console::Console(std::string name)
{   
    main_name = name;
    std::cout << "[ " << main_name << " ]: " << std::endl;
}

void Console::writeLine(std::string line)
{
    std::cout << "[ " << main_name << " ]: " << line << std::endl;
}

void Console::error(std::string error, ERROR_FLAGS flag)
{
    std::cout << "[ " << main_name << " ]: ";
    switch (flag)
    {
    case SDL_ERROR:
        std::cout << SDL_GetError() << std::endl;
        break;
    case IMG_ERROR:
        std::cout << IMG_GetError() << std::endl;
        break;
    case MIX_ERROR:
        std::cout << Mix_GetError() << std::endl;
    default:
        break;
    }
}
