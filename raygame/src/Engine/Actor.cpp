#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

void Actor::addForce(MathLibrary::Vector2 force)
{
    setVelocity(getVelocity() + force);
}

void Actor::start()
{
    m_started = true;

    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->start();
    }
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->onCollision(other);
    }
}

void Actor::checkVelocity()
{
    if (m_velocity.x > m_maxVelocity.x)
        m_velocity.x = m_maxVelocity.x;
    if (m_velocity.y > m_maxVelocity.y)
        m_velocity.y = m_maxVelocity.y;
}

void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();
    checkVelocity();
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->update(deltaTime);
    }
}

void Actor::draw()
{
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->draw();
    }
}

void Actor::end()
{
    m_started = false;
    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->end();
    }
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());

    for (int i = 0; i < m_components.Length(); i++)
    {
        m_components[i]->onDestroy();
    }
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}