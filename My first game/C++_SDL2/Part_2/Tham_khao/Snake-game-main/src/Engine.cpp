///Engine [Source]
#include "Engine.h"

//Project headers
#include "Resources.h"

///Engine class
//static
SDL_Window* Engine::window; /* anh Bá khai báo lại sau static ??? */
SDL_Renderer* Engine::renderer;
bool Engine::running;
int Engine::width, Engine::height;

Console Engine::console("Engine"); /* Hàm init console để main_name là class */

Playing Engine::playing;

//constructor:
Engine::Engine()
{
    window = NULL;
    renderer = NULL;
    running = false;
}

//destructor:
Engine::~Engine()
{
    window = NULL;
    renderer = NULL;
}

//initialize:
void Engine::init(int _width, int _height, std::string title)
{
    width = _width;
    height = _height;

    window = NULL;
    renderer = NULL;

    running = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //Error:
        console.logError("SDL could not initialize!");
        running = false;
    }
    else
    {
        console.writeLine("Initialized SDL.");

        //Create window:
        window = SDL_CreateWindow(title.c_str(),
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         width, height,
                         SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            //Error:
            console.logError("Window could not be created!");
            running = false;
        }
        else
        {
            console.writeLine("Created window.");

            //Create renderer:
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                //Error:
                console.logError("Renderer could not be created!");
                running = false;
            }
            else
            {
                console.writeLine("Created renderer.");

                //Initialize SDL_image
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    //Error:
                    console.logError("SDL_image could not initialize!", IMG_ERROR);
                    running = false; /* Thanh's edition */
                }
                else
                {
                    console.writeLine("Initialized SDL_image.");

                    //Initialize Resouces
                    Resources::init(renderer);
                    Resources::load();

                    //Initialize Playing
                    playing.init(window, renderer);
                }
            }
        }
    }
}

//Game loop condition
bool Engine::isRunning()
{
    return running;
}

//Handle Events from Player
void Engine::handleEvents()
{
    //SDL event
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        //User option
        switch (event.type)
        {
            //Quit the game
            case SDL_QUIT:
                console.writeLine("Closing window. . .");
                running = false;
                break;

            //Key down
            case SDL_KEYDOWN:
                playing.keyPressed(event.key.keysym.sym);
                break;

            //Key up
            case SDL_KEYUP:
                playing.keyReleased(event.key.keysym.sym);
                break;

            default:
                break;
        }
    }
    playing.loop(); /* Vòng lặp trong game */
}

//Render animation
void Engine::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render
    playing.render();

    //Update window
    SDL_RenderPresent(renderer);
}

//Close
void Engine::close() 
{
    //Destroy Playing State
    playing.destroy(); 

    //Free Resources
    Resources::free();

    console.writeLine("Closing Engine. . .");

    //Destroy window & renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
