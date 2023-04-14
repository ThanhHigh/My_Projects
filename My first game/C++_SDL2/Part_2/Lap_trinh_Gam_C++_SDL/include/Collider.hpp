//Collider header
#ifndef COLLIDER_HPP //Check collision by box
#define COLLIDER_HPP

#include "SDL2/SDL.h"

class Collider
{
    public:
        //check collision by using Rectangle by SDL_Rect
        inline SDL_Rect Get(){ return m_Box; }
        //to m_Box only around the char not all the imager. 
        //Change the space of box around the character
        inline void setBuffer(int x, int y, int w, int h)
        {
            m_Buffer = {x, y, w, h};
        }

        void Set(int x, int y, int w, int h)
        {
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h
            };
        }

    private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;
    
};

#endif //COLLIDER_HPP