//Engine [Sources]
#include "Engine.hpp"

//Include Header
#include "Resources.hpp"
#include "Playing.hpp"

#include <SDL2/SDL.h>

//class Engine
//static 
SDL_Window* Engine::window;
SDL_Texture* Engine::texture;
SDL_Renderer* Engine::renderer;

Console Engine::console("Engine");
Playing Engine::playing;

int Engine::width, Engine::height;

bool Engine::running;


//Constructor
Engine::Engine()
{
    running = false;

    window = NULL;
    renderer = NULL;
}

Engine::~Engine()
{
    window = NULL;
    renderer = NULL;
}

void Engine::init(const std::string _title, const int _w, const int _h)
{
    width = _w;
    height = _h;

    //flag
    running = true;

    window = NULL;
    renderer = NULL;

    //Initilize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        //Error:
        console.error("Could not initilize SDL ", ERROR_FLAGS::SDL_ERROR);
        running = false;
    }
    
    else
    {
        console.writeLine("Initilized SDL!");
        //Create a Window
        window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            //Error:
            console.error("Could not create a Window", ERROR_FLAGS::SDL_ERROR);
            running = false;
        }
        else
        {
            console.writeLine("Created a Window!");
            //Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                //Error:
                console.error("Could not create Renderer", ERROR_FLAGS::SDL_ERROR);
                running = false;
            }
            else
            {
                console.writeLine("Created Renderer");
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    //Error:
                    console.error("Could not load PNG", ERROR_FLAGS::IMG_ERROR);
                    running = false;
                }
                else
                {
                    console.writeLine("Initilized PNG loading");

                    //Initilize Resources
                    Resources::init(renderer);
                    Resources::load();

                    //Initilize Playing
                    playing.init(window, renderer);
                }
            }
        }
    }
    
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
        //User option
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            console.writeLine("Closing Window");
            break;
        //key_down
        case SDL_KEYDOWN:
            playing.keyPress(event.key.keysym.sym);
            break;

        //key_up
        case SDL_KEYUP:
            playing.keyRelease(event.key.keysym.sym);
            break;
        
        default:
            break;
        }
    }
}

void Engine::update()
{
    playing.loop();
}

void Engine::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
    SDL_RenderClear(renderer);

    //Render
    playing.render();
    
    //Update window
    SDL_RenderPresent(renderer);
}

int Engine::get_width()
{
    return width;
}

int Engine::ger_height()
{
    return height;
}

void Engine::close()
{
    //Destroy Playing State
    playing.destroy();

    //Free Resources
    Resources::free();
    console.writeLine("Freeing Resources");

    //Destroy window & renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL
    SDL_Quit();
}