
#include "Warrior.hpp"
#include "TextureManager.hpp"
#include "KeyboardInput.hpp"

#include <SDL2/SDL.h>

Warrior::Warrior(Properties* props) : Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();


}

void Warrior::drawObject()
{
    m_Animation->drawAnimation(m_Transform->X, m_Transform->Y, m_Width, m_Height);

}

void Warrior::updateObject(float deltaTime)
{
    //Time
    m_RigidBody->updateRigidBody(deltaTime); //Debug deltaTime = 0.2;
    //Key control

    m_Animation->setPropsAnimation(m_TextureID, 1, 10, 80, SDL_FLIP_NONE);
    m_RigidBody->unsetForce();

    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_J))
    {
            m_Animation->setPropsAnimation("Player_AttackCombo", 1, 10, 70, SDL_FLIP_HORIZONTAL);
    }

    if(KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_A))
    {
        m_Animation->setPropsAnimation("Player_Run", 1, 10, 80, SDL_FLIP_HORIZONTAL);
        m_RigidBody->applyForceX(1*LEFTWARD);
    }

    if(KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_D))
    {
        m_Animation->setPropsAnimation("Player_Run", 1, 10, 80, SDL_FLIP_NONE);
        m_RigidBody->applyForceX(1*RIGHTWARD);
    }
    
    //Update DeltaTime
    m_RigidBody->updateRigidBody(deltaTime);

    //Transform
    m_Transform->transLateX(m_RigidBody->getPosition().X);
    //Animation
    m_Animation->updateAnimation();
}

void Warrior::cleanObject()
{
    TextureManager::getInstance()->cleanTexture();
}