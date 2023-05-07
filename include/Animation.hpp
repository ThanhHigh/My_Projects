#ifndef Animation_hpp
#define Animation_hpp

#include <SDL2/SDL.h>

#include <string>

class Animation
{
public:
    Animation(){}

    void updateAnimation();
    void drawAnimation(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setPropsAnimation(std::string textureID, int spriteRow, int frameCount, int animSpeed);
private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimationSpeed, m_FrameCount;
    std::string m_TextureID;
};


#endif //Animation_hpp