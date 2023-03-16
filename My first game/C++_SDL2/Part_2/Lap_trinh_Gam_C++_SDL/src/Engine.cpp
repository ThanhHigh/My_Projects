#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Warrior.hpp"
#include "KeyboardInput.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "Camera.hpp"

#include <iostream>

#include <SDL2/SDL_image.h>

KeyboardInput* KeyboardInput::s_Instance = nullptr;
Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
Warrior* player = nullptr;


bool Engine::initGame()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initilize SDL: %s ", SDL_GetError());
        return false;
    }

    //Window Flag
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Window",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 window_flags);
    
    if (m_Window == nullptr) 
    {
        SDL_Log("Failed to create a Window: %s ", SDL_GetError());
        return false;
    }

    m_Renderer =  SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_Renderer == nullptr)
    {
        SDL_Log("Failed to create a Renderer: %s ", SDL_GetError());
        return false;
    }

    //Map
    if (MapParser::GetInstance()->load() == false) //Check error:
    {
        std::cout << "Failed to load map" << std::endl;
    }

    //If Map is oke
    m_level0map = MapParser::GetInstance()->GetMap("map1");


    TextureManager::getInstance()->loadTexture("Player_Fall", "res/_Fall.png");
    TextureManager::getInstance()->loadTexture("Player_Run", "res/_Run.png");
    TextureManager::getInstance()->loadTexture("Player","res/_Idle.png");
    TextureManager::getInstance()->loadTexture("Player_AttackCombo", "res/_AttackCombo.png");
    TextureManager::getInstance()->loadTexture("Back_ground", "res/Back_ground.png");

    player = new Warrior (new Properties("Player", 100, 200, 120, 80));

    //Take the target value of player
    Camera::getInstance()->setTarget(player->getOrigin());

    return m_Running = true;
}
void Engine::updateGame()
{
    float deltaTime = Timer::GetInstance()->getDeltaTime();

    m_level0map->update();

    player->updateObject(deltaTime);

    Camera::getInstance()->update(deltaTime);
}
void Engine::renderGame()
{
    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 191, 148, 228, 120);

    //render Background
    TextureManager::getInstance()->draw("Back_ground", 0, 0, 1920, 640);
    //Render map
    m_level0map->render();
    //Player
    player->drawObject();
    
    SDL_RenderPresent(m_Renderer);
}
void Engine::eventsGame()
{
    KeyboardInput::getInstance()->Listen();
}
void Engine::quitGame()
{
    m_Running = false;
}
void Engine::clearGame()
{
    TextureManager::getInstance()->cleanTexture();
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    IMG_Quit();
    SDL_Quit();

}