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
void RigidBody::applyForceY(float force_y = 0)
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

void RigidBody::setPosition(float X, float Y)
{
    Vector2D temppos(X, Y);
    m_Position = temppos;
}

void RigidBody::setVelocity(float X, float Y)
{
    Vector2D tempvel(X, Y);
    m_Velocity = tempvel;
}
void RigidBody::setAccelarate(float X, float Y)
{
    Vector2D tempacc(X, Y);
    m_Accelaration = tempacc;
}

void RigidBody::setVelocityY(float Y)
{
    m_Velocity.Y = Y;
}

void RigidBody::setAccelarateY(float Y)
{
    m_Accelaration.Y = Y;
}


//Update
void RigidBody::updateRigidBody(float deltaTime)
{
    //Accelarate
    m_Accelaration.Y = m_Force.Y/ m_Mass + m_Gravity;
    m_Accelaration.X = (m_Force.X + m_Friction.X) / m_Mass;

    //Velocity
    m_Velocity = m_Accelaration*deltaTime;
    // m_Velocity = m_Velocity + m_Accelaration*deltaTime;


    //Position
    m_Position = m_Velocity*deltaTime;
    m_Position = m_Position + m_Velocity*deltaTime;

    // //Verlet Velocity Function
    // float DeltaTime = deltaTime * 0.5;
    // m_Accelaration.X = 0; m_Accelaration.Y = 0;

    // //Position
    // m_Position = m_Velocity*DeltaTime + m_Accelaration * DeltaTime * DeltaTime * 0.5;
    // // m_Position = m_Position + m_Velocity*DeltaTime + m_Accelaration * DeltaTime* DeltaTime * 0.5;

    // //Accelarate
    // m_newAccelaration.Y = m_Force.Y/ m_Mass + m_Gravity;
    // m_newAccelaration.X = (m_Force.X + m_Friction.X) / m_Mass;

    // //Velocity
    // // m_Velocity = m_Velocity + (m_Accelaration + m_newAccelaration) * DeltaTime * 0.5;
    // m_Velocity = (m_Accelaration + m_newAccelaration) * DeltaTime * 0.5;

    // m_Accelaration = m_newAccelaration;
}