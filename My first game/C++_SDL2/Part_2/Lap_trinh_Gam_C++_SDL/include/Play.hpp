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

class Play : public GameState
{
    public:
        Play();
        void event();
        virtual bool init();
        virtual bool exit();
        virtual void update();
        virtual void render();
        // inline GameMap* getMap(){ return m_levelMap; }
    private:
        static void openMenu();
        static void pauseGame();
    private:
        bool m_editmode;
        GameMap* m_levelMap;
        std::vector<GameObject*> m_GameObjects;
};

#endif //Play_hpp