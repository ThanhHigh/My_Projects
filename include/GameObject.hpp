#ifndef GameObject_hpp
#define GameObject_hpp

#include "IObject.hpp"
#include "Transform.hpp"
#include "Points.hpp"
#include <SDL2/SDL.h>

//This for to pass the value to constructor of GameObject faster
struct Properties
{  
    public:
    //Constructor
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        {
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            TextureID = textureID;
        }


    public:
        //Copy from the GameObject class

        float X, Y; // Take the value X, Y from Transform GameObject
        int Width, Height;
        std::string TextureID;
        SDL_RendererFlip Flip;
    
};


class GameObject : public IObject
{
    public:
        GameObject(Properties* props)
        {
            m_TextureID = props->TextureID;
            m_Width = props->Width;
            m_Height = props->Height;
            m_Flip = props->Flip;
            //Transform pointer need to init here, if do not will cause bugs cz of Pointers
            m_Transform = new Transform(props->X, props->Y);
            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_Origin = new Points(px, py);

        }

        inline Points* getOrigin() { return m_Origin; }

        virtual void drawObject() = 0;
        virtual void updateObject(float deltaTime) = 0;
        virtual void cleanObject() = 0;

    protected: //To create out inheritance system( the concept where one class 'inherits' from another class  )
        Points* m_Origin; 
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
        
};

#endif //GameObject_hpp