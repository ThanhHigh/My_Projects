//Engine [Source]
#include "Engine.hpp"

//Include Header
#include "Console.hpp"

//Engine class:
//Constructor:

Engine::Engine()
{
    //Window
    window = NULL;
    renderer = NULL;

    //Information
    width = height = 0;
    title = "";

    //Status:
    running = true;

    //Console
    console = NULL;

    //System
    system = NULL;

    //State

    return;
}

Engine::~Engine()
{
    //Destroy Console
    running = false;

    delete console;
    console = NULL;

    //Destroy System
    delete system;
    system = NULL;

    //Destroy State
    
}

//Initilization
void Engine::init(const std::string _title, const int _width, const int _height)
{   
    //Initilize flag
    running = true;

    //Initilize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //Error:
        console->logError("Could not initilize SDL!", ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Initilized SDL!");

    //Create Window
    width = _width;
    height = _height;
    title = _title;
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        //Error:
        console->logError("Could not load Window!",ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Created Window!");

    //Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        //Error:
        console->logError("Could not load Renderer!",ERROR_FLAGS::SDL_ERROR);
        running = false;
        return;
    }
    console->writeLine("Created Renderer!");

    //Initialize System    
    
    //Initialize Audio

    //Initialize Graphic

    //Initialize Timer

    //Initialize Control


    //Load system config


    //Initialize State
}   

bool Engine::isRunning()
{
    return running;
}

void Engine::handleEvent()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        
        case SDL_KEYDOWN:
            break;

        case SDL_KEYUP:
            
            break;
        default:
            break;
        }
    }
}

void Engine::render()
{
    //Render
    
    //Update screen
}

void Engine::loop()
{

}

void Engine::close()
{

}
