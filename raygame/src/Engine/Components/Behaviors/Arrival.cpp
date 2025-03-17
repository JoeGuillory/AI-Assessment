#include "Arrival.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>
Arrival::Arrival(): Behavior::Behavior()
{
}

Arrival::Arrival(Actor* owner, Actor* target, float maxspeed, float weight) : Behavior::Behavior(owner,target,maxspeed,weight)
{
}

Arrival::Arrival(Actor* owner, MathLibrary::Vector2 point, float maxspeed, float weight)
{
	m_owner = owner;
	m_point = point;
	m_maxSpeed = maxspeed;
	m_weight = weight;
}

Arrival::~Arrival()
{
}

void Arrival::start()
{
}

void Arrival::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			float distance = (m_target->getTransform()->getWorldPosition() - m_owner->getTransform()->getWorldPosition()).getMagnitude();

			m_owner->addForce(SteeringForce(m_target->getTransform()->getWorldPosition(),m_owner->getTransform()->getWorldPosition(),fmin((distance / m_radius), m_owner->getMaxSpeed()) * m_weight * deltaTime));
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}
		else
		{
			float distance = (m_point - m_owner->getTransform()->getWorldPosition()).getMagnitude();

			m_owner->addForce(SteeringForce(m_point, m_owner->getTransform()->getWorldPosition(), fmin((distance / m_radius), m_owner->getMaxSpeed())) * m_weight * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Arrival::end()
{
}
