#ifndef Animation_hpp
#define Animation_hpp

#include <SDL2/SDL.h>

#include <string>

class Animation
{
public:
    Animation(){}

    void updateAnimation();
    void drawAnimation(float x, float y, int spriteWidth, int spriteHeight);
    void setPropsAnimation(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimationSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};


#endif //Animation_hpp