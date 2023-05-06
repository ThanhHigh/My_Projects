
#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "MapParser.hpp"

TileLayer::TileLayer(int tilesize, int colcount, int rowcount, tileMap tilemap, tileSetList tilesets) 
    :m_TileSize (tilesize),
    m_ColCount(colcount),
    m_RowCount(rowcount),
    m_TileMap(tilemap),
    m_TileSets(tilesets)
{
    //Constructor for load texture
    for (unsigned int i = 0; i < m_TileSets.size(); i++)
    {
        TextureManager::getInstance()->loadTexture(m_TileSets[i].name, "res/" + m_TileSets[i].source);
    }
}

void TileLayer::render()
{
    for (int i = 0; i < m_RowCount; i++)
    {
        for (int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_TileMap[i][j];

            if (tileID == 0) continue; 
            // Make sure tileID = 0 will be skip.
            // Time run map will reduce considerabley
            else
            {
                int index = 0;
                if (m_TileSets.size() >= 1) //Debug: ban dau la > 1
                {
                    //if we have one tileset
                    for (unsigned int k = 1; k < m_TileSets.size(); k++)
                    {
                        if (tileID >= m_TileSets[k].firstID && tileID <= m_TileSets[k].lastID)
                        {
                            tileID = tileID + m_TileSets[k].tileCount - m_TileSets[k].lastID;
                            index = k;
                            break;
                        }
                    }
                }

                TileSet ts = m_TileSets[index];
                int tileRow = tileID / ts.colCount;
                int tileCol = tileID - tileRow * ts.colCount - 1;

                //if this tile is on the las collumn
                if (tileID % ts.colCount == 0)
                {
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }


                TextureManager::getInstance()->drawtile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::render(int p_x, int p_y)
{
    int toadox, toadoy;
    toadox = p_x;
    toadoy = p_y;
    for (int i = 0; i < m_RowCount; i++)
    {
        for (int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_TileMap[i][j];

            if (tileID == 0) continue; 
            // Make sure tileID = 0 will be skip.
            //Time run map will reduce considerabley
            else
            {
                int index = 0;
                if (m_TileSets.size() > 1)
                {
                    //if we have one tileset
                    for (unsigned int k = 1; k < m_TileSets.size(); k++)
                    {
                        if (tileID >= m_TileSets[k].firstID && tileID <= m_TileSets[k].lastID)
                        {
                            tileID = tileID + m_TileSets[k].tileCount - m_TileSets[k].lastID;
                            index = k;
                            break;
                        }
                    }
                }

                TileSet ts = m_TileSets[index];
                int tileRow = tileID / ts.colCount;
                int tileCol = tileID - tileRow * ts.colCount - 1;

                //if this tile is on the las collumn
                if (tileID % ts.colCount == 0)
                {
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }


                TextureManager::getInstance()->drawtile(ts.name, ts.tileSize, toadox + j * ts.tileSize, toadoy + i * ts.tileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::update()
{

}
