#include "Behavior.h"
#include "Actor.h"
#include "Transform2D.h"
#include <algorithm>

Behavior::Behavior() : Component::Component()
{
}

Behavior::Behavior(Actor* owner, Actor* target, float maxspeed, float weight) : m_target(target), m_maxSpeed(maxspeed), m_weight(weight)
{
	m_owner = owner;
	if (m_weight > 1)
		m_weight = 1;
	if (m_weight < 0)
		m_weight = 0;
	m_enabled = true;
}

Behavior::~Behavior()
{
}

void Behavior::start()
{
}

void Behavior::update(float deltaTime)
{
}

void Behavior::end()
{
}

void Behavior::setWeight(float weight)
{
	if (!(weight < 0) || !(weight > 1))
		m_weight = weight;
	else
		return;

}

MathLibrary::Vector2 Behavior::SteeringForce(MathLibrary::Vector2 lhs, MathLibrary::Vector2 rhs, float maxSpeed)
{
	MathLibrary::Vector2 desiredVelocity = (lhs - rhs).getNormalized() * maxSpeed;
	return desiredVelocity - m_owner->getVelocity();
}




