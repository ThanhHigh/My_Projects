//BackWall
#ifndef BackWall_hpp
#define BackWall_hpp

#include "TextureManager.hpp"
#include "Animation.hpp"


class BackWall
{

    public:

        inline static BackWall* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new BackWall();
        }
        //set up
        bool createBackWall();
        //draw
        void draw();

        //position

        //collision player & update

        //Deconstructor
        ~BackWall();
    private:
        static BackWall* s_Instance;
        Animation* b_Animation;
};


#endif //BackWall_hpp