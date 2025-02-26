#include "Seek.h"
#include "Actor.h"
#include "Transform2D.h"
#include <cmath>

Seek::Seek() : Behavior::Behavior()
{
}

Seek::Seek(Actor* owner, Actor* target, float maxspeed, float weight) : Behavior::Behavior(owner, target, maxspeed, weight)
{

}

Seek::~Seek()
{
}

void Seek::start()
{
}

void Seek::update(float deltaTime)
{
	if (m_enabled)
	{
		if (m_owner && m_target)
		{
			m_owner->addForce(SteeringForce(m_target->getTransform()->getLocalPosition(),m_owner->getTransform()->getLocalPosition(),m_maxSpeed) * m_weight * deltaTime);
			m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
			m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
		}

	}
}

void Seek::end()
{
}
