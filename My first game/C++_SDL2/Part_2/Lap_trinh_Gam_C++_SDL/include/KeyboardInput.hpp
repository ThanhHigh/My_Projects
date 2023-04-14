#ifndef KeyboardInput_hpp
#define KeyboardInput_hpp

#include <SDL2/SDL.h>

enum Axis {HORIZONTAL, VERTICAL};

class KeyboardInput
{
public:
    KeyboardInput();
    
    static KeyboardInput* getInstance()
    {
        return s_Instance = (s_Instance != nullptr)? s_Instance : new KeyboardInput();
    }

    void Listen();
    bool getKeyDown(SDL_Scancode key);

    int getAxisKey(Axis axis);

private:
    void keyUp();
    void keyDown();

    const Uint8* m_KeyStates;
    static KeyboardInput* s_Instance;
};

#endif //KeyboardInput_hpp