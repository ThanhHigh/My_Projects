//Play_cpp
#include "Play.hpp"
#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Warrior.hpp"
#include "KeyboardInput.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "Camera.hpp"
#include "BackWall.hpp"
#include "BackWall.hpp"
#include "KeyboardInput.hpp"

GameMap* Play :: m_currMap = nullptr;
Warrior* warrior = nullptr;

Play::Play(){}

bool Play::init()
{   
    //flag
    bool success = true;
    m_Ctxt = Engine::GetInstance()->getRenderer();

    if (MapParser::GetInstance()->load() == false) 
    {
        std::cout << "Failed to load map" << std::endl;
    }
    // //Collision
    // TileLayer* collisionLayer = (TileLayer*)Play::getMap()->m_GetMapLayers().back();
    // tileMap collisionTileMap = collisionLayer->getTileMap();
    // int tilesize = collisionLayer->getTileSize();
    // CollisionHandler::getInstance()->setCollisionMap(collisionTileMap, tilesize);

    Play::createLevel();

    //Player Warior
    warrior = new Warrior (new Properties("Player", 400, 10, 120, 80));

    TextureManager::getInstance()->parseTextures("res/Texture.tml");

    //Camera
    Camera::getInstance()->setTarget(warrior->getOrigin());
    //GameObject
    m_GameObjects.push_back(warrior);
    //Map
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
    //BackWall
    if (!(BackWall::GetInstance()->createBackWall())) success = false;
    std::cout << "play initialized" << std::endl;
    return success;
}

void Play::update()
{
    //get deltaTime
    float deltaTime = Timer::GetInstance()->getDeltaTime();
    //Map
    updateLevelMap();
    //Event()
    event();
    // //GameObject update
    // for (auto gameobj : m_GameObjects)
    //     gameobj->updateObject(deltaTime);
    warrior->updateObject(deltaTime);

    //Camera updtae
    Camera::getInstance()->update(deltaTime);
    //BackWall
    BackWall::GetInstance()->udpate();
}

void Play::render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 120, 50, 60, 220);
    SDL_RenderClear(m_Ctxt);

    //Render and update map to infinity
    render_update_LevelPart();
    //Rect camera
    SDL_Rect camera = Camera::getInstance()->getViewBox();
    // //Loop draw objiect
    // for (auto gameobj : m_GameObjects)
    //     gameobj->drawObject();
    //Player
    warrior->drawObject();

    //BackWall
    BackWall::GetInstance()->draw();

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::openMenu()
{
    //Engine::GetInstance().changstate( new Menu());
}

void Play::pauseGame()
{
    
}

void Play::event()
{
    KeyboardInput::getInstance()->Listen();
}

bool Play::exit()
{
    //Clean Map
    
    // //Clean Obj
    // for (auto gameobj : m_GameObjects)
    // {
    //     gameobj->cleanObject();
    //     delete gameobj;
    // }
    // m_GameObjects.clear();

    //Texture Clear
    TextureManager::getInstance()->cleanTexture();
    SDL_DestroyRenderer(m_Ctxt);
    m_Ctxt = nullptr;
    std::cout << "Exit Play" << std::endl;
    return true;
}   


void Play::updateLevelMap()
{
    // for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    // {
    //         int LevelPosX = m_LevelPartMapList.at(i).getX();
    //         int ObjectX  = Camera::getInstance()->getTargetPos()->x;
    //         int viewBoxX = Camera::getInstance()->getPosition().X;
    //         if (ObjectX >= LevelPosX && ObjectX <= (LevelPosX + LEVEL_WIDTH - 1))
    //         {
                
    //             m_currMap = m_LevelPartMapList.at(i).getMapfromLevel();
    //             break;
    //         }
    // }
}

bool Play::createLevel()
{
    // for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    // {
    //         int random = rand() % (TOTAL_MAP - 1);
    //         if (i == 0) random = TOTAL_MAP - 1;
    //         GameMap* mapTemp = m_MapList.at(random);
    //         LevelPart level(i * LEVEL_WIDTH, 0, mapTemp);
    //         m_LevelPartMapList.push_back(level);
    // }

    // if (m_LevelPartMapList.size() < TOTAL_LEVEL_MAP)
    // {
    //     std::cout << "Failed to create Level!" << std::endl;
    // }
}

void Play::render_update_LevelPart()
{
    // //Debug check x viewbox
    // int LevelPosX = m_LevelPartMapList.at(0).getX();
    // int viewBoxX  = Camera::getInstance()->getViewBox().x;
    // if ((LevelPosX - viewBoxX) <= (-LEVEL_WIDTH + 1)) 
    // {
    //     int setXlevelMap = m_LevelPartMapList.at(m_LevelPartMapList.size() - 1).getX();
    //     setXlevelMap += LEVEL_WIDTH;
    //     int random = rand() % (TOTAL_MAP - 1);
    //     GameMap* mapTemp = m_MapList.at(random);
    //     m_LevelPartMapList.at(0).setLevelMap(mapTemp);
    //     m_LevelPartMapList.at(0).setLevelX(setXlevelMap);

    //     LevelPart level = m_LevelPartMapList.at(0);
    //     m_LevelPartMapList.erase(m_LevelPartMapList.begin());
    //     m_LevelPartMapList.push_back(level);
    // }
    // if (viewBoxX == 0)
    // {
    //     for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    //     {
    //         m_LevelPartMapList.at(i).renderLevelPart(i * LEVEL_WIDTH);       
    //     }
    //     // m_level0map->render();
    // }
    // else
    // {
    //     for (int i = 0; i < TOTAL_LEVEL_MAP; i++)
    //     {
    //         m_LevelPartMapList.at(i).renderLevelPart();
    //     }
    // }
}

