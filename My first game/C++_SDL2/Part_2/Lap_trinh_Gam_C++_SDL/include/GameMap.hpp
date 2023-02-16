#ifndef GameMap_hpp
#define GameMap_hpp

#include "Layer.hpp"

#include <vector> //to define array of Layers could have in Map

class GameMap
{
    public:
        void renderMapGame()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
                m_MapLayers[i]->renderLayer();
        }

        void updateMapGame()
        {
            for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            {
                m_MapLayers[i]->updateLayer();
            }
        }

        inline std::vector m_GetMapLayers() { return m_MapLayers; }
    private:
        std::vector <Layer*> m_MapLayers;
};

#endif //GameMap_hpp