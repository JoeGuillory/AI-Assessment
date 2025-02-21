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
			m_owner->addForce(ArriveForce(m_radius) * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Arrival::end()
{
}
