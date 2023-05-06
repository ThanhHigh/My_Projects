#ifndef GameMap_hpp
#define GameMap_hpp

#include "Layer.hpp"

#include <vector> //to define array of Layers could have in Map

class GameMap
{
    public:
        void render()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
                m_MapLayers[i]->render();
        }

        void render(int p_x, int p_y)
        {
            X = p_x;
            Y = p_y;
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
                m_MapLayers[i]->render(p_x, p_y);
        }

        void update()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            {
                m_MapLayers[i]->update();
            }
        }

        inline int getMapX(){ return X; }
        inline void setMapX(int p_x){ X = p_x; }

        inline std::vector <Layer*> m_GetMapLayers() { return m_MapLayers; }
    private:
        friend class MapParser;
        std::vector < Layer* > m_MapLayers;
        int X, Y; //Position of GameMap
};


#endif //GameMap_hpp