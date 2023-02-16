//RigidBody [Source]
#include "RigidBody.hpp"

//Initilize
RigidBody::RigidBody()
{
    m_Mass = UNKNOWN_MASS;
    m_Gravity = GRAVITY;
}

//Set properties
void RigidBody::setMass(float mass)
{
    m_Mass = mass;
}
void RigidBody::setGravity(float gravity)
{
    m_Gravity = gravity;
}
float RigidBody::getMass()
{
    return m_Mass;
}
float RigidBody::getGravity()
{
    return m_Gravity;
}
Vector2D RigidBody::getForce()
{
    return m_Force;
}
Vector2D RigidBody::getFriction()
{
    return m_Friction;
}
Vector2D RigidBody::getPosition()
{
    return m_Position;
}
Vector2D RigidBody::getVelocity()
{
    return m_Velocity;
}
Vector2D RigidBody::getAccelaration()
{   
    return m_Accelaration;
}

//Set up world physical
//Forces
void RigidBody::applyForce(Vector2D force)
{
    m_Force = force;
}
void RigidBody::applyForceX(float force_x)
{   
    m_Force.X = force_x;
}
void RigidBody::applyForceY(float force_y)
{
    m_Force.Y = force_y;
}
void RigidBody::unsetForce()
{
    m_Force = Vector2D(0, 0);
}

void RigidBody::applyFriction(Vector2D friction)
{
    m_Friction = friction;
}

void RigidBody::applyFrictionX(float friction_x)
{
    m_Friction.X = friction_x;
}
void RigidBody::unsetFriction()
{
    m_Friction = Vector2D(0, 0);
}


//Update
void RigidBody::updateRigidBody(float deltaTime)
{
    //Accelarate
    m_Accelaration.Y = m_Force.Y/ m_Mass + m_Gravity;
    m_Accelaration.X = (m_Force.X + m_Friction.X) / m_Mass;

    //Velocity
    m_Velocity = m_Accelaration*deltaTime;

    //Position
    m_Position = m_Velocity*deltaTime;
}