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

    m_Window = SDL_CreateWindow("RuntheSky",
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
    m_MapList.push_back(m_level0map);
    m_level1map = MapParser::GetInstance()->GetMap("map2");
    m_MapList.push_back(m_level1map);
    m_level2map = MapParser::GetInstance()->GetMap("map3");
    m_MapList.push_back(m_level2map);
    m_level3map = MapParser::GetInstance()->GetMap("map4");
    m_MapList.push_back(m_level3map);
    m_level4map = MapParser::GetInstance()->GetMap("map5");
    m_MapList.push_back(m_level4map);
    m_levelspawnmap = MapParser::GetInstance()->GetMap("map_spawn");
    m_MapList.push_back(m_levelspawnmap);

    //Debug
    // std::cout << m_MapList.size() << std::endl;
    
    Engine::GetInstance()->createLevel();

    player = new Warrior (new Properties("Player", 400, 320, 120, 80));

    TextureManager::getInstance()->parseTextures("res/Texture.tml");

    // TextureManager::getInstance()->loadTexture("Player_Fall", "res/_Fall.png");
    // TextureManager::getInstance()->loadTexture("Player_Run", "res/_Run.png");
    // TextureManager::getInstance()->loadTexture("Player","res/_Idle.png");
    // TextureManager::getInstance()->loadTexture("Player_AttackCombo", "res/_AttackCombo.png");
    // TextureManager::getInstance()->loadTexture("Player_Jump", "res/_Jump.png");
    // TextureManager::getInstance()->loadTexture("Player_Crouch", "res/_Crouch.png");
    // TextureManager::getInstance()->loadTexture("Player_AttackNoMovement", "res/_AttackNoMovement.png");
    // TextureManager::getInstance()->loadTexture("Player-AttackComboNoMovement", "res/_AttackComboNoMovement.png");
    // TextureManager::getInstance()->loadTexture("Back_ground", "res/back_ground_2.png");


    //Take the target value of player
    Camera::getInstance()->setTarget(player->getOrigin());

    return m_Running = true;
}
void Engine::updateGame()
{
    float deltaTime = Timer::GetInstance()->getDeltaTime();
    
    for (int i = 0; i < m_MapList.size(); i++)
        m_MapList[i]->update();

    player->updateObject(deltaTime);

    Camera::getInstance()->update(deltaTime);
}
void Engine::renderGame()
{
    SDL_RenderClear(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 191, 148, 228, 120);

    //render Background
    TextureManager::getInstance()->draw("Back_ground", 0, 0, 1920, 1080);
    //Render map

    // //Debug add level
    // m_level2map->render(LEVEL_WIDTH, 0);
    // // m_level3map->render(LEVEL_WIDTH * 2, 0);
    // for (int i = 0; i < m_MapList.size(); i++)
    //     m_MapList[i]->render();


    //Render and update map to infinity
    render_update_LevelPart();

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

bool Engine::createLevel()
{
    for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    {
            int random = rand() % (TOTAL_MAP - 1);
            if (i == 0) random = TOTAL_MAP - 1;
            GameMap* mapTemp = m_MapList.at(random);
            LevelPart level(i * LEVEL_WIDTH, 0, mapTemp);
            m_LevelPartMapList.push_back(level);
    }

    if (m_LevelPartMapList.size() < TOTAL_LEVEL_MAP)
    {
        std::cout << "Failed to create Level!" << std::endl;
    }
}

void Engine::render_update_LevelPart()
{
    //Debug check x viewbox
    int LevelPosX = m_LevelPartMapList.at(0).getX();
    int viewBoxX  = Camera::getInstance()->getViewBox().x;
    if ((LevelPosX - viewBoxX) <= (-LEVEL_WIDTH + 1)) 
    {
        int setXlevelMap = m_LevelPartMapList.at(m_LevelPartMapList.size() - 1).getX();
        setXlevelMap += LEVEL_WIDTH;
        int random = rand() % (TOTAL_MAP - 1);
        GameMap* mapTemp = m_MapList.at(random);
        m_LevelPartMapList.at(0).setLevelMap(mapTemp);
        m_LevelPartMapList.at(0).setLevelX(setXlevelMap);

        LevelPart level = m_LevelPartMapList.at(0);
        m_LevelPartMapList.erase(m_LevelPartMapList.begin());
        m_LevelPartMapList.push_back(level);
    }

    if (viewBoxX < LEVEL_WIDTH)
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart(i * LEVEL_WIDTH);           
        }
        // m_level0map->render();
    }
    else
    {
        for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
        {
            m_LevelPartMapList.at(i).renderLevelPart();
        }
    }
}
