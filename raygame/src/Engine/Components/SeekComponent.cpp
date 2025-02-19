#include "SeekComponent.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"
#include <cmath>
SeekComponent::SeekComponent()
{
	m_target = nullptr;
	m_enabled = true;
}

SeekComponent::SeekComponent(Actor* owner, Actor* target, float max_velocity)
{
	m_owner = owner;
	m_target = target;
	m_maxSpeed = max_velocity;
	m_enabled = true;
}

SeekComponent::~SeekComponent()
{
}

void SeekComponent::start()
{
	
}

void SeekComponent::update(float deltaTime)
{	
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			MathLibrary::Vector2 desiredVelocity = (m_target->getTransform()->getWorldPosition() - m_owner->getTransform()->getWorldPosition()).normalize() * m_maxSpeed;
			MathLibrary::Vector2 steeringForce = desiredVelocity - m_owner->getVelocity();
			m_owner->addForce(steeringForce * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}
	}
}

void SeekComponent::end()
{
}
