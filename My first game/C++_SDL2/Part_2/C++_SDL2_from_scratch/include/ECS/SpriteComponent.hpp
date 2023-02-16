//SpriteComponent [Head]
#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

//Project lib
#include "Components.hpp"
#include "../TextureManager.hpp"

//SDL lib
#include <SDL2/SDL.h>

//C++ lib
#include <string>

class SpriteComponent : public Component
{
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(std::string path)
        {
            setTex(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(std::string path)
        {
            texture = TextureManager::loadTexture(path);
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;


        }

        void update() override
        {
            destRect.x = (int)transform->position.x;
            destRect.y = (int)transform->position.y;

            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;


        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }

};
#endif //SpriteComponent_hpp