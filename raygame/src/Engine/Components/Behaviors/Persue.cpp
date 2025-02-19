#include "Persue.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>
Persue::Persue()
{
}

Persue::Persue(Actor* owner, Actor* target, float maxspeed, float weight) : Behavior::Behavior(owner,target,maxspeed,weight)
{
}

Persue::~Persue()
{
}

void Persue::start()
{
}

void Persue::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			m_owner->addForce(PursueForce() * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Persue::end()
{
}
