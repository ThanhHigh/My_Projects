#ifndef ENGINE_HPP
#define ENGINE_hPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameMap.hpp"
#include "MapParser.hpp"
#include "LevelPart.hpp"

// #define SCREEN_WIDTH 1344
// #define SCREEN_HEIGHT 768

// const int SCREEN_WIDTH = 1344;
// const int SCREEN_HEIGHT = 768;

const int TOTAL_MAP = 6;
const int TOTAL_LEVEL_MAP = 3;

class Engine
{

public:
    //getInstance to make sure that it only has one Engine for whole program
    static Engine* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }
    bool initGame();
    void quitGame();
    void clearGame();

    void updateGame();
    void renderGame();
    void render_update_LevelPart();
    bool createLevel();
    void eventsGame();

    inline GameMap* getMap(){ return m_currMap; }
    inline bool isRunningGame(){ return m_Running; }
    inline SDL_Renderer* getRenderer(){ return m_Renderer; }
    
private:
    Engine(){}

    static Engine* s_Instance;
    bool  m_Running;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    GameMap* m_level0map;
    GameMap* m_level1map;
    GameMap* m_level2map;
    GameMap* m_level3map;
    GameMap* m_level4map;
    GameMap* m_levelspawnmap;
    //When render alaways update current map
    GameMap* m_currMap;

    // An aray to store levelmap list
    std::vector <GameMap*> m_MapList;
    std::vector <LevelPart> m_LevelPartMapList;
};

#endif //ENGINE_HPP