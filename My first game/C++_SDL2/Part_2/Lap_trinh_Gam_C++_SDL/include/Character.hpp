#ifndef Character_hpp
#define Character_hpp

#include "GameObject.hpp"

#include <string>

class Character : public GameObject
{
    public:
        Character(Properties* props)  : GameObject(props) {}

        virtual void drawObject() = 0;
        virtual void updateObject(float dt) = 0;
        virtual void cleanObject() = 0;

    protected:
        std::string m_Name;
};

#endif //Character_hpp
