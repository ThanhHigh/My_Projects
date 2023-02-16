//Game [Source]
#include "Game.hpp"
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "ECS/Components.hpp"
#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

//Projec#t lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ lib
#include <iostream>
#include <string>

//Variables
TileMap* Map = NULL;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& Player(manager.addEntity());
SDL_Event Game::event;
auto& Wall(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flag = 0;
    if (fullscreen)
    {
        flag = SDL_WINDOW_FULLSCREEN;
    } 

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initilize SDL ! Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else
    {
        window = SDL_CreateWindow((title.c_str()), xpos, ypos, width, height, flag);

        if (window == NULL)
        {
            std::cout << "Could not initilize Window ! Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else 
        {
            renderer = SDL_CreateRenderer(window, -1, 0);

            //Color
            SDL_SetRenderDrawColor(renderer, 152, 115, 172, 0);

            if (renderer == NULL)
            {
                std::cout << "Could not initilize Render ! Error: " << SDL_GetError() << std::endl;
                isRunning = false;
            }

            else
            {
                Map = new TileMap();

                //ECS implimentation
                Player.addComponent<TransformComponent>(0,0);
                Player.addComponent<SpriteComponent>("res/dark_knight.png");
                Player.addComponent<KeyboardController>();
                Player.addComponent<ColliderComponent>("player");

                Wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
                Wall.addComponent<SpriteComponent>("res/dirt.png");
                Wall.addComponent<ColliderComponent>("wall");


            }
        }
    }
}

void Game::HandleEvent()
{
    SDL_PollEvent(&event);
    {
        switch (event.type)
        {
        case (SDL_QUIT):
            isRunning = false;
            break;
        
        default:
            break;
        }
    }
}

void Game::Update()
{
    //Refresh
    manager.refresh();

    //ECS update
    manager.update();

    //Others update
    
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    //render stuff here
    Map->DrawMap();

    //ECS render
    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();

    std::cout << "Game Closing. . ." << std::endl;

    SDL_Delay(1000);
}

bool Game::running()
{
    return isRunning;
}
