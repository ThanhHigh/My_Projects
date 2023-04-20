//BackWall [source]
#include <iostream>

#include "BackWall.hpp"
#include "Camera.hpp"
#include "CollisionHandler.hpp"

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
    b_Animation->drawAnimation(X + 2, Y + 2, 256, 1280);
}



//positon
void BackWall::udpate()
{
    //Chase Char
    X = Camera::getInstance()->getViewBox().x;
    Y = Camera::getInstance()->getViewBox().y;

    

    
}

BackWall::~BackWall()
{
    TextureManager::getInstance()->dropTexture("BackWall");
}