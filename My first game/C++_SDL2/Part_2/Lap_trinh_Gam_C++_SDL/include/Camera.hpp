#ifndef Camera_hpp
#define Camera_hpp

#include "SDL2/SDL.h"
#include "Points.hpp"
#include "Vector2D.hpp"

// #define SCREEN_WIDTH 1344
// #define SCREEN_HEIGHT 768

const int SCREEN_WIDTH = 1344;
const int SCREEN_HEIGHT = 768;

class Camera
{
    public:
        //Only one camera function
        inline static Camera* getInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new Camera();
        }
        //methods

        //Get viewbox
        inline SDL_Rect getViewBox() { return m_ViewBox; }
        inline Vector2D getPosition() { return m_position; }
        inline void setTarget(Points* target) { m_target = target; }
        inline Points* getTargetPos() { return m_target; }


        void update(float deltatime);


    private:
        Camera() { m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }
        //tagert camera follow
        Points* m_target;
        Vector2D m_position;

        //view box
        SDL_Rect m_ViewBox;

        static Camera* s_instance;
        friend class Engine;
};


#endif //camera_hpp