//Play_hpp
#ifndef Play_hpp
#define Play_hpp

#include <iostream>
#include "GameMap.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
// #include "Enemy.hpp"
#include "Warrior.hpp"
#include "Timer.hpp"
#include "Menu.hpp"
#include "KeyboardInput.hpp"
#include "Camera.hpp"
#include "MapParser.hpp"
#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "CollisionHandler.hpp"
#include "LevelPart.hpp"

class Play : public GameState
{
    public:
        Play();
        void event();
        bool init();
        bool exit();
        void update();
        void render();
        
        void updateLevelMap();
        bool createLevel();
        void render_update_LevelPart();
        static GameMap* getMap(){ return m_currMap; }
    private:
        static void openMenu();
        static void pauseGame();
    private:
        static GameMap* m_currMap;
        bool m_editmode;
        GameMap* m_level0map;
        GameMap* m_level1map;
        GameMap* m_level2map;
        GameMap* m_level3map;
        GameMap* m_level4map;
        GameMap* m_levelspawnmap;
        std::vector <GameMap*> m_MapList;
        std::vector <LevelPart> m_LevelPartMapList;
        //GameObject
        std::vector<GameObject*> m_GameObjects;
};

#endif //Play_hpp