//Console [Sources]
#include "Console.hpp"

//Include Header
#include <iostream>

//Console class
//Constructor
Console::Console(std::string name)
{
    main_name = name;
    return;
}

Console::~Console()
{
    
}

void Console::writeLine(std::string line)
{
    std::cout << "[ " << main_name << " ]: " << line << std::endl;
    return;
}

void Console::logError(std::string error, ERROR_FLAGS flag)
{
    std::cout << " [ " << main_name << " ] - Error: " << error;

    switch (flag)
    {
    case SDL_ERROR:
        std::cout << " - SDL Error: " << SDL_GetError() << std::endl;
        break;
    case IMG_ERROR:
        std::cout << " - SDL Imagge Error: " << IMG_GetError() << std::endl;
        break;
    case MIX_ERROR:
        std::cout << " - SDL Mixer Error: " << Mix_GetError() << std::endl;
        break;
    
    default:
        std::cout << " - Unknown Error: " << std::endl;
        break;
    }
}   