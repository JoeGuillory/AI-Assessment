#include "Behavior.h"
#include "Actor.h"
#include "Transform2D.h"

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

MathLibrary::Vector2 Behavior::SeekForce()
{
	MathLibrary::Vector2 desiredVelocity = (m_target->getTransform()->getWorldPosition() - m_owner->getTransform()->getWorldPosition()).normalize() * m_maxSpeed;
	return desiredVelocity - m_owner->getVelocity();
}

MathLibrary::Vector2 Behavior::FleeForce()
{
	MathLibrary::Vector2 desiredVelocity = (m_owner->getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).normalize() * m_maxSpeed;
	return desiredVelocity - m_owner->getVelocity();
}

MathLibrary::Vector2 Behavior::PursueForce()
{
	MathLibrary::Vector2 desiredVelocity = (m_target->getTransform()->getWorldPosition() + m_target->getVelocity() - m_owner->getTransform()->getWorldPosition()).normalize() * m_maxSpeed;
	return desiredVelocity - m_owner->getVelocity();
}

MathLibrary::Vector2 Behavior::EvadeForce()
{
	MathLibrary::Vector2 desiredVelocity = (m_owner->getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).normalize() + m_target->getVelocity() * m_maxSpeed;
	return desiredVelocity - m_owner->getVelocity();
}

MathLibrary::Vector2 Behavior::ArriveForce()
{
	return MathLibrary::Vector2();
}


