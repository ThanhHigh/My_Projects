
#include "Warrior.hpp"
#include "TextureManager.hpp"
#include "KeyboardInput.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "CollisionHandler.hpp"

#include <SDL2/SDL.h>

Warrior::Warrior(Properties* props) : Character(props)
{
    //Set default
    m_isRunning = false;
    m_IsJumping = false;
    m_isFalling = false;
    m_IsGrounded = false;
    m_isAttacking = false;
    m_isCrouching = false;
    m_isComboAttacking = false;
    m_isDead = false;

    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;
    m_ComboAttackingTime = ATTACKCOMBO_TIME;
    m_DeathTime = DEATH_TIME;

    m_Collider = new Collider;
    m_Collider->setBuffer(-50, -35, 85, 55);

    m_RigidBody = new RigidBody();
    m_RigidBody->setGravity(GRAVITY); 
    m_RigidBody->setMass(KNIGHT_MASS);
    
    m_Animation = new Animation();
    m_Animation->setPropsAnimation(m_TextureID, 1, 10, 80);

}

void Warrior::drawObject()
{
    m_Animation->drawAnimation(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    // //Debug: Add m_Transform->Log();
    // m_Transform->Log();

    // //temporary draw box collider
    // Vector2D cam = Camera::getInstance()->getPosition();
    // SDL_Rect box = m_Collider->Get();
    // box.x -= cam.X; //Recaculate the position of the box
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(), &box);
}

void Warrior::updateObject(float deltaTime)
{
    m_isRunning = false;
    m_isCrouching = false;
    m_RigidBody->unsetForce();

    //Run Forward
    if (KeyboardInput::getInstance()->getAxisKey(HORIZONTAL) == FORWARD && !m_isAttacking && !m_isComboAttacking)
    {
        m_RigidBody->applyForceX(RIGHTWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_isRunning = true;
    }

    //Back-ward
    if (KeyboardInput::getInstance()->getAxisKey(HORIZONTAL) == BACKWARD && !m_isAttacking && !m_isComboAttacking)
    {
        m_RigidBody->applyForceX(LEFTWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_isRunning = true;
    }

    //Crouch
    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_S))
    {
        m_RigidBody->unsetForce();
        m_isCrouching = true;
    }

    //Attack
    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_J))
    {
        m_RigidBody->unsetForce();
        m_isAttacking = true;
    }
    //AttackCombo
    if (KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_J) && KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_S))
    {
        m_RigidBody->unsetForce();
        m_isComboAttacking = true;
    }

    // //Debug
    // if (m_IsGrounded)
    // {
    //     //Make charater stop at
    //     // m_RigidBody->setAccelarateY(0.0f);
    //     m_RigidBody->setVelocityY(0.0f);
    //     m_RigidBody->applyForceY(-50.0f);
    //     // m_RigidBody->applyFriction(10.0);
    // }
    // //Debug

    //Jump
    if ((KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_K) || KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_W) || KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->applyForceY(UPWARD * m_JumpForce * 5);
    }
    if ((KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_K) || KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_W) || KeyboardInput::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= deltaTime;
        m_IsGrounded = false;
        m_RigidBody->applyForceY(UPWARD * m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //Fall
    if (m_RigidBody->getVelocity().Y > 0 && !m_IsGrounded)
    {
        m_isFalling = true;
        m_RigidBody->setGravity(GRAVITY/1.5);
    }
    else{
        m_isFalling = false;
        m_RigidBody->setGravity(GRAVITY);
    }

    //Attack timer
    if ((m_isAttacking) && m_AttackTime > 0)
    {
        m_AttackTime -= deltaTime;
    }
    else{
        m_isAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    //Attack Combo Timer
    if (m_isComboAttacking && m_ComboAttackingTime > 0)
    {
        m_ComboAttackingTime -= deltaTime;
    }
    else{
        m_isComboAttacking = false;
        m_ComboAttackingTime = ATTACKCOMBO_TIME;
    }

    //Move on X axis
    m_RigidBody->updateRigidBody(deltaTime);
    m_LastSafePosition.X = m_Transform->X; //Safe the safe position of char before update
    m_Transform->X += m_RigidBody->getPosition().X; //Update the transform then update collider !
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    if (CollisionHandler::getInstance()->MapCollision(m_Collider->Get()))   
    {
        m_Transform->X = m_LastSafePosition.X;
    
    }

    //move on Y axis
    m_RigidBody->updateRigidBody(deltaTime);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->getPosition().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    if (CollisionHandler::getInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    // if (m_IsJumping)
    // {
    //     m_Animation->setPropsAnimation("Player_Jump", 1, 3, 100);
    // }

    // // Debug
    // // m_Transform->Log();

    //Move on X axis
    // m_RigidBody->updateRigidBody(deltaTime);
    // m_LastSafePosition.X = m_Transform->X; //Safe the safe position of char before update
    // m_Transform->X = m_RigidBody->getPosition().X; //Update the transform then update collider !
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    // if (CollisionHandler::getInstance()->MapCollision(m_Collider->Get()))   
    // {
    //     m_Transform->X = m_LastSafePosition.X;
    //     // float tempN_ForeceX = m_RigidBody->getForce().X;
    //     // m_RigidBody->applyForceX(-tempN_ForeceX);
    // }

    // //move on Y axis
    // m_RigidBody->updateRigidBody(deltaTime);
    // m_LastSafePosition.Y = m_Transform->Y;
    // m_Transform->Y = m_RigidBody->getPosition().Y;
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    // if (CollisionHandler::getInstance()->MapCollision(m_Collider->Get()))
    // {
    //     if (m_RigidBody->getVelocity().Y > 0)
    //     {
    //         if (m_isFalling)
    //         {
    //             m_IsGrounded = true;
    //             //m_RigidBody->setGravity(0.0f);
    //         }
    //     }
    //     else if (m_RigidBody->getVelocity().Y < 0)
    //     {
    //         Vector2D temp = m_RigidBody->getPosition();
    //         temp = temp - m_RigidBody->getVelocity();
    //         m_RigidBody->setPosition(temp.X, temp.Y);
    //         m_RigidBody->setVelocity(0.0, 0.0);
    //     }
    //     m_Transform->Y = m_LastSafePosition.Y;
    // }
    // else
    // {
    //     m_IsGrounded = false;
    // }

    // if (m_IsJumping)
    // {
    //     m_Animation->setPropsAnimation("Player_Jump", 1, 3, 100);
    // }

    //Fall infinity
    if (m_RigidBody->getPosition().Y >= SCREEN_HEIGHT)
    {
        m_RigidBody->setPosition(30,10);
        //Debug cout
    }
    //Fall infinity

    // //Log
    // // m_RigidBody->getPosition().Log();
    // //Debug

    
    //Udpate Origin(Camera view)
    m_Origin->x = m_Transform->X + m_Width/2; //Debug
    m_Origin->y = m_Transform->Y + m_Height/2; //Debug

    if (m_Origin->x < 256 && !(m_isDead) && (m_DeathTime > 0)) 
    {
        m_isDead = true;
        m_DeathTime -= deltaTime;
        if (m_DeathTime <= 0 && m_Origin->x > 256)
        {
            m_isDead = false;
            m_DeathTime = DEATH_TIME;
        }
    }
    //Animation
    AnimationState();
    m_Animation->updateAnimation();

    
}

void Warrior::AnimationState()
{
    //Idle
    m_Animation->setPropsAnimation("Player", 1, 10, 100);

    //Running
    if (m_isRunning)
        m_Animation->setPropsAnimation("Player_Run", 1, 10, 100);

    //Crouching
    if (m_isCrouching)
        m_Animation->setPropsAnimation("Player_Crouch", 1, 1, 120);

    //Jumping
    if (m_IsJumping)
        m_Animation->setPropsAnimation("Player_Jump", 1, 3, 100);  

    //Failing
    if (m_isFalling)
        m_Animation->setPropsAnimation("Player_Fall", 1, 3, 120);

    //Attack
    if (m_isAttacking)
    {
        m_Animation->setPropsAnimation("Player_AttackNoMovement", 1, 4, 150);
    }

    //ComboAttack
    if (m_isComboAttacking)
    {
        m_Animation->setPropsAnimation("Player_AttackComboNoMovement", 1, 10, 70);
    }

    if (m_IsJumping)
    {
        m_Animation->setPropsAnimation("Player_Jump", 1, 3, 100);
    }

    if (m_isDead)
    {
        m_Animation->setPropsAnimation("Player_Dead", 1, 10, 100);
    }
}


void Warrior::cleanObject()
{
    TextureManager::getInstance()->dropTexture(m_TextureID);
}