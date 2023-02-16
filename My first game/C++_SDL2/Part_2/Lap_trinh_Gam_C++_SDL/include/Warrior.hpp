#ifndef Warrior_hpp
#define Warrior_hpp

#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"

class Warrior : public Character
{
public:
    Warrior(Properties* props);

    virtual void drawObject();
    virtual void updateObject(float deltaTime);
    virtual void cleanObject();
private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
};


#endif //Warrior_hpp