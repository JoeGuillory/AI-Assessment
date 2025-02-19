#include "FleeComponent.h"
#include "Vector2.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Vector2.h"
#include <cmath>
FleeComponent::FleeComponent()
{
	m_enabled = true;
}

FleeComponent::FleeComponent(Actor* owner, Actor* target, float maxspeed): m_target(target), m_maxSpeed(maxspeed)
{
	m_owner = owner;
	m_enabled = true;
}

FleeComponent::~FleeComponent()
{
}

void FleeComponent::start()
{
}

void FleeComponent::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			MathLibrary::Vector2 desiredVelocity = (m_owner->getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).normalize() * m_maxSpeed;
			MathLibrary::Vector2 steeringForce = desiredVelocity - m_owner->getVelocity();
			m_owner->addForce(steeringForce * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}
	}
}

void FleeComponent::end()
{
}
