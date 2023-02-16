#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

//Project lib
#include "ECS.hpp"
#include "Components.hpp"

//SDL lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ lib
#include <string>

class ColliderComponent : public Component
{
    SDL_Rect collider; //rect collision
    std::string tag; // tag is what things do when collision
public:
    ColliderComponent(std::string temp)
    {
        tag = temp;
    }

    TransformComponent* transform;

    //make sure we have transform component to game run correctly
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    //Change transformComponent for Collision
    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }


};

#endif //ColliderComponent_hpp