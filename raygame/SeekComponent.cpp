#include "SeekComponent.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"
SeekComponent::SeekComponent()
{
	m_target = nullptr;
}

SeekComponent::SeekComponent(Actor* owner, Actor* target, float max_velocity)
{
	m_owner = owner;
	m_target = target;
	m_maxSpeed = max_velocity;
}

SeekComponent::~SeekComponent()
{
}

void SeekComponent::start()
{
	
}

void SeekComponent::update(float deltaTime)
{	
	if (m_owner && m_target)
	{
		MathLibrary::Vector2 desiredVelocity = (m_target->getTransform()->getLocalPosition().normalize() - m_owner->getTransform()->getLocalPosition().normalize()) * m_maxSpeed;
		MathLibrary::Vector2 steeringForce = desiredVelocity - m_owner->getVelocity();
		m_owner->setVelocity(steeringForce * deltaTime);
		m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
	}

}

void SeekComponent::end()
{
}
