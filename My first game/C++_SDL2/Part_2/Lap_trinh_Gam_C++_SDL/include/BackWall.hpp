//BackWall
#ifndef BackWall_hpp
#define BackWall_hpp

#include "TextureManager.hpp"


class BackWall
{

    public:
        ~BackWall();
        inline static BackWall* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new BackWall();
        }

        //render
        
        //position

        //collision player



    private:
        static BackWall* s_Instance;
};


#endif //BackWall_hpp