#include "Seek.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>



Seek::Seek() : Behavior::Behavior()
{
}

Seek::Seek(Actor* owner, Actor* target, float maxspeed, float weight) : Behavior::Behavior(owner, target, maxspeed, weight)
{
	
	m_selected = TARGET;
}

Seek::Seek(Actor* owner, MathLibrary::Vector2 point, float maxSpeed, float weight)
{
	m_owner = owner;
	m_point = point;
	m_maxSpeed = maxSpeed;
	m_weight = weight;
	m_selected = POINT;
}

Seek::~Seek()
{
}

void Seek::start()
{
}

void Seek::update(float deltaTime)
{
	if (m_enabled)
	{
		switch (m_selected)
		{
			case TARGET:
			{
				if (!m_target)
					break;
				m_owner->addForce(SteeringForce(m_target->getTransform()->getLocalPosition(), m_owner->getTransform()->getLocalPosition(), m_owner->getMaxSpeed()) * m_weight * deltaTime);
				m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
				m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
				break;
			}
			case POINT:
			{
				m_owner->addForce(SteeringForce(m_point, m_owner->getTransform()->getLocalPosition(), m_owner->getMaxSpeed()) * m_weight * deltaTime);
				m_owner->getTransform()->translate(m_owner->getVelocity() * m_owner->getMaxSpeed() * deltaTime);
				m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
				break;
			}
		}
	}
}

void Seek::end()
{
}
