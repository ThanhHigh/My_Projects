#ifndef RigidBody_hpp
#define RigidBody_hpp

#include "Vector2D.hpp"

//Const
const float UNKNOWN_MASS = 0.6;
const float GRAVITY = 5.0f; 

const float RIGHTWARD = 1; //x
const float LEFTWARD = -1;
const float UPWARD = -1; //
const float DOWNWARD = 1;

// bool RIGHTSIGHT;
// bool LEFTSIGHT;
// bool UPSIGHT;
// bool DOWNSIGHT;

class RigidBody
{
    public:
        //Initilize
        RigidBody();
        //Set properties & Get properties
        void setMass(float mass);
        void setGravity(float gravity);

        float getMass();
        float getGravity();
        Vector2D getForce();
        Vector2D getFriction();
        Vector2D getPosition();
        Vector2D getVelocity();
        Vector2D getAccelaration();

        //set
        void setPosition(float X, float Y);
        void setVelocity(float X, float Y);
        void setAccelarate(float X, float Y);
        void setVelocityY(float Y);
        void setAccelarateY(float Y);
        
        //Set up world physical
        //Forces
        void applyForce(Vector2D force);
        void applyForceX(float force_x);
        void applyForceY(float force_y);
        void unsetForce();
        //Friction
        void applyFriction(Vector2D friction);
        void applyFrictionX(float friction_x);
        void unsetFriction();

        //Udpate
        void updateRigidBody(float deltaTime);
    
    private:
        float m_Mass;
        float m_Gravity;

        //Control force of characer ex when falling, jumping,...
        Vector2D m_Force;
        //Control friction force(lực ma sát) ex walk on grass, dirt, ice,...
        Vector2D m_Friction;

        Vector2D m_Position; //Vị trí
        Vector2D m_Velocity; //Vận tốc
        Vector2D m_Accelaration; //Gia tốc
        Vector2D m_newAccelaration;
};


#endif //RigidBody_hpp
