//PositionComponent [Head]
#ifndef TransformComponent_hpp
#define TransformComponent_hpp

//Poject source
#include "Components.hpp"
#include "../Vector2D.hpp"


class TransformComponent : public Component
{
    public:
        Vector2D position;
        Vector2D velocity;

        int speed = 3;

        //Set up
        int height = 32;
        int width = 32;
        int scale = 1;

        TransformComponent(int x, int y)
        {
            position.x = x;
            position.y = y;
        }

        TransformComponent(float x, float y, int h, int w, int sc)
        {
            position.x = x;
            position.y = y;
            height = h;
            width = w;
            scale = sc;
        }

        TransformComponent()
        {
            position.x = 0.0f;
            position.y = 0.0f;
        }

        void init() override
        {
            velocity.x = 0;
            velocity.y = 0;
        }

        void update() override
        {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};

#endif //TransformComponent_hpp