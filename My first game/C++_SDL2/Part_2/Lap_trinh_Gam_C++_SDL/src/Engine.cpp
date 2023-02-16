#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Warrior.hpp"
#include "KeyboardInput.hpp"
#include "Timer.hpp"

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

    m_Window = SDL_CreateWindow("Window",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 0);
    
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

    TextureManager::getInstance()->loadTexture("Player_Fall", "res/_Fall.png");
    TextureManager::getInstance()->loadTexture("Player_Run", "res/_Run.png");
    TextureManager::getInstance()->loadTexture("Player","res/_Idle.png");
    TextureManager::getInstance()->loadTexture("Player_AttackCombo", "res/_AttackCombo.png");

    player = new Warrior (new Properties("Player", 100, 200, 120, 80));

    return m_Running = true;
}
void Engine::updateGame()
{
    float deltaTime = Timer::GetInstance()->getDeltaTime();
    player->updateObject(deltaTime);
}
void Engine::renderGame()
{
    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 134, 156, 87, 180);

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