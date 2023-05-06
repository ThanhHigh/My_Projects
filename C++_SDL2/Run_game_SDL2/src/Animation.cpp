#include "Animation.hpp"

#include "TextureManager.hpp"

void Animation::updateAnimation()
{
    //This line make Frame loop correctly: If the frame go beyond the limit, set to 0
    // the more m_AnimationSpeed, the slower animation is
    m_SpriteFrame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void Animation::drawAnimation(float x, float y, int spriteWidth, int spriteHeight,  SDL_RendererFlip flip)
{
    TextureManager::getInstance()->drawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}

void Animation::setPropsAnimation(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimationSpeed = animSpeed;
}