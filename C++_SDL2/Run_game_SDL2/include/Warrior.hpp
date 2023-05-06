#ifndef Warrior_hpp
#define Warrior_hpp

#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Vector2D.hpp"

//Constances
#define KNIGHT_MASS 3.0f
#define JUMP_TIME 15.0f
#define JUMP_FORCE 30.0f
#define RUN_FORCE  6.0f
#define ATTACKCOMBO_TIME 40.0f
#define ATTACK_TIME 33.0f
#define DEATH_TIME 35.0f


const int FORWARD = 1;
const int BACKWARD = -1;

class Warrior : public Character
{
public:
    Warrior(Properties* props);

    virtual void drawObject();
    virtual void updateObject(float deltaTime);
    virtual void cleanObject();
    inline bool Dead() { return m_isDead; }
    inline void setLive() { m_isDead = false; }
    void playAgain();
private:
    void AnimationState();

private:
    //state
    bool m_isRunning;
    bool m_IsJumping;
    bool m_isFalling;
    bool m_IsGrounded;
    bool m_isAttacking;
    bool m_isCrouching;
    bool m_isComboAttacking;
    bool m_isDead;

    //bool m_isHurting;
    float m_AttackTime;
    float m_ComboAttackingTime;
    float m_JumpTime; //How Long Player can Jump
    float m_JumpForce; 
    float m_DeathTime;

    Collider* m_Collider; //Box around the Player
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Vector2D m_LastSafePosition; //Make sure Player hit the wall bring player back the wall so player wont stuck
};


#endif //Warrior_hpp