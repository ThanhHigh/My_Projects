#ifndef Warrior_hpp
#define Warrior_hpp

#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Vector2D.hpp"

//Constances
#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f;

class Warrior : public Character
{
public:
    Warrior(Properties* props);

    virtual void drawObject();
    virtual void updateObject(float deltaTime);
    virtual void cleanObject();
private:
    bool m_IsJumping;
    bool m_IsGrounded;

    float m_JumpTime; //How Long Player can Jump
    float m_JumpForce; 

    Collider* m_Collider; //Box around the Player
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Vector2D m_LastSafePosition; //Make sure Player hit the wall bring player back the wall so player wont stuck
};


#endif //Warrior_hpp