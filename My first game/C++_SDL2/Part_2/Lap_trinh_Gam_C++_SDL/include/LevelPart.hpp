
#ifndef LevelPart_hpp
#define LevelPart_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MapParser.hpp"
#include "GameMap.hpp"

#include <string>
#include <vector>

const int LEVEL_WIDTH = 1344;

class LevelPart
{

    public:
        
        inline static LevelPart* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new LevelPart();
        }
        inline int getX() { return x; }
        inline int getY() { return y; }
        inline void setX(int _x) { x = _x; }
        inline void setY(int _y) { y = _y; }

        LevelPart(){}
        LevelPart(int p_x, int p_y, GameMap* gamemap);
        void setLevelMap(GameMap* gamemap);
        void renderLevelPart();
        void renderLevelPart(int p_x);
        void setLevelX(GameMap* gameMap);
        void setLevelX(int p_x);
        inline GameMap* getMapfromLevel(){ return levelgamemap; }


    private:
        static LevelPart* s_Instance;
        friend class MapParser;
        friend class Engine;
        int x = 0, y = 0;
        GameMap* levelgamemap = nullptr;
};

#endif //LevelPart_hpp