
#include "KeyboardInput.hpp"
#include "Engine.hpp"


KeyboardInput::KeyboardInput()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void KeyboardInput::Listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Engine::GetInstance()->quitGame();
            break;
        case SDL_KEYDOWN:
            keyDown();
            break;
        case SDL_KEYUP:
            keyUp();
            break;
        //Mouse
        case SDL_MOUSEMOTION:
        {
            m_MouseClick = false;
            //Save mouse posi
            SDL_GetMouseState(&x, &y);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            m_MouseClick = true;
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            m_MouseClick = false;
            break;
        }
        default:
            break;
        }
    }
    
}

bool KeyboardInput::getKeyDown(SDL_Scancode key)
{
    if (m_KeyStates[key] == 1) return true;
    else return false;
}

void KeyboardInput::keyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void KeyboardInput::keyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

int KeyboardInput::getAxisKey(Axis axis)
{
    int res;
    switch (axis)
    {
    case HORIZONTAL:
        if (getKeyDown(SDL_SCANCODE_D) || getKeyDown(SDL_SCANCODE_RIGHT))
            res = 1;
        if (getKeyDown(SDL_SCANCODE_A) || getKeyDown(SDL_SCANCODE_LEFT))
            res = -1;
        break;
    
    case VERTICAL:
        if (getKeyDown(SDL_SCANCODE_W) || getKeyDown(SDL_SCANCODE_UP))
            res = 1;
        if (getKeyDown(SDL_SCANCODE_S) || getKeyDown(SDL_SCANCODE_DOWN))
            res = -1;
        break;
    default:
        res = 0;
        break;
    }
    return res;
}

bool KeyboardInput::mouseover(SDL_Rect textureRect)
{
    if (x < textureRect.x) return false;
    if (x > textureRect.x + textureRect.w ) return false;
    if (y < textureRect.y) return false;
    if (y > textureRect.y + textureRect.h) return false; 
    return true;
}

bool KeyboardInput::mouseclick()
{
    return m_MouseClick;
}
