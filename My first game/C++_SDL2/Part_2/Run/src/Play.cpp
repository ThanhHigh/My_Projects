//Play_cpp
#include "Play.hpp"
#include "Engine.hpp"

Play::Play(){}

bool Play::init()
{
    m_Ctxt = Engine::GetInstance()->getRenderer();

    TextureManager::getInstance()->parseTextures("res/Texture.tml");
    //Collision
    TileLayer* collisionLayer = (TileLayer*)Engine::GetInstance()->getMap()->m_GetMapLayers().back();
    tileMap collisionTileMap = collisionLayer->getTileMap();
    int tilesize = collisionLayer->getTileSize();
    CollisionHandler::getInstance()->setCollisionMap(collisionTileMap, tilesize);

    //Player Warior
    Warrior* warrior = nullptr;
    warrior = new Warrior (new Properties("Player", 400, 10, 120, 80));
    //Camera
    Camera::getInstance()->setTarget(warrior->getOrigin());
    //GameObject
    m_GameObjects.push_back(warrior);
    std::cout << "play initialized" << std::endl;
    return true;
}

void Play::render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 120, 50, 60, 220);
    SDL_RenderClear(m_Ctxt);

    //render map

    //Rect camera
    SDL_Rect camera = Camera::getInstance()->getViewBox();
    //Loop draw objiect
    for (auto gameobj : m_GameObjects)
        gameobj->drawObject();

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::update()
{
    //get deltaTime
    float deltaTime = Timer::GetInstance()->getDeltaTime();
    //Event()
    event();
    //GameObject update
    for (auto gameobj : m_GameObjects)
        gameobj->updateObject(deltaTime);

    //Camera updtae
    Camera::getInstance()->update(deltaTime);
    //Map update
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
    
}

bool Play::exit()
{
    //Clean Map

    //Clean Obj
    for (auto gameobj : m_GameObjects)
    {
        gameobj->cleanObject();
        delete gameobj;
    }
    m_GameObjects.clear();
    //Texture Clear
    TextureManager::getInstance()->cleanTexture();
    std::cout << "Exit Play" << std::endl;
}   
