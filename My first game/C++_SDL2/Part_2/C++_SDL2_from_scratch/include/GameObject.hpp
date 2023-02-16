//GameObject [Header]
#ifndef GameObject_hpp
#define GameObject_hpp

//Project Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//C++ lib
#include <string>

class GameObject
{
    public:
        GameObject(std::string texturesheet, SDL_Renderer* ren, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:
        int xpos, ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;      
};

#endif //GameObject_hpp