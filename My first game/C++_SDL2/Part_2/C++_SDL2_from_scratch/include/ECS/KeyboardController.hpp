//KeyboardController [Head]
#ifndef KeyboardController_hpp
#define KeyboardController_hpp

//Project lib
#include "ECS.hpp"
#include "../Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
    public:

        //Create transform components for entity
        TransformComponent* transform;

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
        }

        void update() override
        {
            //Check whether we have Key Event or not
            if (Game::event.type == SDL_KEYDOWN)
            {
                //Key pressed
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transform->velocity.y = -1;//up
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;//down
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;//right
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;//left
                default:
                    break;
                }
            }

            if (Game::event.type == SDL_KEYUP)
            {
                //Key release
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transform->velocity.y = 0;//up
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;//down
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;//right
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;//left
                default:
                    break;
                }
            }
        }
};


#endif //KeyboardController_hpp