#include "Camera.hpp"

//Initilize our instances
Camera* Camera::s_instance = nullptr;

void Camera::update(float deltatime)
{
    //Check whether target exist
    if (m_target != nullptr)
    {
        m_ViewBox.x = m_target->x - SCREEN_WIDTH / 2;
        m_ViewBox.y = m_target->y - SCREEN_HEIGHT / 2;

        if (m_ViewBox.x < 0)
        {
            m_ViewBox.x = 0;
        }

        if (m_ViewBox.y < 0)
        {
            m_ViewBox.y = 0;
        }

        if (m_ViewBox.x > (2*SCREEN_WIDTH - m_ViewBox.w))
        {
            m_ViewBox.x = (2*SCREEN_WIDTH - m_ViewBox.w);
        }

        if (m_ViewBox.y > (2*SCREEN_HEIGHT - m_ViewBox.h))
        {
            m_ViewBox.y = (2*SCREEN_HEIGHT - m_ViewBox.h);
        }

        m_position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}