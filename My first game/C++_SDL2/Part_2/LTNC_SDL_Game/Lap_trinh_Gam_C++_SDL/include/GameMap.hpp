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

        void update()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            {
                m_MapLayers[i]->update();
            }
        }

        inline std::vector <Layer*> m_GetMapLayers() { return m_MapLayers; }
    private:
        friend class MapParser;
        std::vector < Layer* > m_MapLayers;
};

#endif //GameMap_hpp