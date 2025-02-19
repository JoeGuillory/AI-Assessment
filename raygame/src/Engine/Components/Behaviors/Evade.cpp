#include "Evade.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>

Evade::Evade() : Behavior::Behavior()
{
}

Evade::Evade(Actor* owner, Actor* target, float maxspeed, float weight) : Behavior::Behavior(owner, target, maxspeed,weight)
{
}

Evade::~Evade()
{
}

void Evade::start()
{
}

void Evade::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			m_owner->addForce(EvadeForce() * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Evade::end()
{
}
