#include "Camera.hpp"

//Initilize our instances
Camera* Camera::s_instance = nullptr;


void Camera::update(float deltatime)
{
    //Check whether target exist
    if (m_target != nullptr)
    {
        if (m_target->x + 16 - m_ViewBox.x >= 0.6 * float(SCREEN_WIDTH))
            m_ViewBox.x = m_target->x + 16 - 0.6 * float(SCREEN_WIDTH);

        m_ViewBox.y = m_target->y - SCREEN_HEIGHT;

        if (m_ViewBox.x < 0)
        {
            m_ViewBox.x = 0;
        }

        if (m_ViewBox.y < 0)
        {
            m_ViewBox.y = 0;
        }

        if (m_ViewBox.y > SCREEN_HEIGHT - m_ViewBox.h)
        {
            m_ViewBox.y = SCREEN_HEIGHT - m_ViewBox.h;
        }
    }

    //Chase the Char with Velocity
    //When main char is not dead
    m_ViewBox.x += camVel;
    if (camVel < 4) camAcc = WALL_ACC;
    if (camVel > 4) camAcc = 0.0005;
    camVel += camAcc;
    if (camVel >= 5) camVel = WALL_VEL_MAX;

    //Udate Position
    m_position = Vector2D(m_ViewBox.x, m_ViewBox.y);
}

void Camera::playAgain()
{
    m_ViewBox.x = 0;
    m_ViewBox.y = 0;
    camVel = 0;
}