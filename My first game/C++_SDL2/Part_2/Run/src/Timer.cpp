#include "Timer.hpp"

#include <SDL2/SDL.h>

Timer* Timer::s_Instance;

void Timer::timerTicks()
{
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS/1000.0f);
    if (m_DeltaTime > TARGET_DELTATIME)
    {
        m_DeltaTime = TARGET_DELTATIME;
    }

    m_LastTime = SDL_GetTicks();
}