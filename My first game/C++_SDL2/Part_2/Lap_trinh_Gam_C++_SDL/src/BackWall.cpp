//BackWall [source]
#include <iostream>

#include "BackWall.hpp"

BackWall* BackWall::s_Instance = nullptr;

bool BackWall::createBackWall()
{ 
    bool flag = true;
    b_Animation = new Animation;
    if (b_Animation != nullptr) {
        std::cout << "Create BackWall" << std::endl;
        flag = true;
    }
    else
    {
        std::cout << "Can not create BackWall" << std::endl;
        flag = false;
    }

    //set Animation
    b_Animation->setPropsAnimation("BackWall", 1, 15, 100);

    return flag;
}

void BackWall::draw()
{
    //update Animation
    b_Animation->updateAnimation();

    //draw
    b_Animation->drawAnimation(10, 10, 256, 1280);
}

//draw
BackWall::~BackWall()
{
    TextureManager::getInstance()->dropTexture("BackWall");
}
