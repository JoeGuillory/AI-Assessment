#include "Wander.h"
#include <random>
#include "Actor.h"
#include "Transform2D.h"
#include "raylib.h"
Wander::Wander() : Behavior::Behavior()
{
}

Wander::Wander(Actor* owner, float maxspeed,float weight)
{
	m_owner = owner;
	m_maxSpeed = maxspeed;
	m_unitScaler = 20;
	m_distance = 100;
	m_enabled = true;
	if (weight > 1)
		m_weight = 1;
	else if (weight < 0)
		m_weight = 0;
	else
		m_weight = weight;
}

Wander::~Wander()
{
}

void Wander::start()
{
	m_time = 0;
}

void Wander::update(float deltaTime)
{
	MathLibrary::Vector2 newDestination;
	if (m_enabled)
	{
		m_time -= 1 * deltaTime;
		if (m_time < 0)
		{
			newDestination = getDestination();
			
			m_time = 1.5;
		}
		m_owner->addForce(SteeringForce(newDestination, m_owner->getTransform()->getLocalPosition(), m_maxSpeed) * m_weight * deltaTime);
		m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
		m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
	}

}

void Wander::end()
{
}

MathLibrary::Vector2 Wander::getDestination()
{
	
	float randX = GetRandomValue(-10, 10);
	float randY = GetRandomValue(-10, 10);
	MathLibrary::Vector2 randpoint = { randX,randY };
	randpoint = (randpoint.getNormalized() * m_unitScaler) + m_owner->getTransform()->getLocalPosition() + (m_owner->getTransform()->getForward() * m_distance);
	return randpoint;
}

