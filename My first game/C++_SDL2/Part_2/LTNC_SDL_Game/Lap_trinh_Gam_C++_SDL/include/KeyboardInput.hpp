#ifndef KeyboardInput_hpp
#define KeyboardInput_hpp

#include <SDL2/SDL.h>

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

private:
    static KeyboardInput* s_Instance;
    void keyUp();
    void keyDown();

    const Uint8* m_KeyStates;

};



#endif //KeyboardInput_hpp