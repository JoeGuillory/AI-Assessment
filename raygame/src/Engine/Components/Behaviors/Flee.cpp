#include "Flee.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>
Flee::Flee() : Behavior::Behavior()
{
}

Flee::Flee(Actor* owner, Actor* target, float maxSpeed, float weight) : Behavior::Behavior(owner,target,maxSpeed,weight)
{
}

Flee::~Flee()
{
}

void Flee::start()
{
}

void Flee::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			m_owner->addForce(FleeForce() * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Flee::end()
{
}
