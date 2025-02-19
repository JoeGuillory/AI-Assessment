#include "Wander.h"
#include <random>
#include "Actor.h"
#include "Transform2D.h"
#include "raylib.h"
Wander::Wander() : Behavior::Behavior()
{
}

Wander::Wander(Actor* owner, float maxspeed)
{
	m_owner = owner;
	m_maxSpeed = maxspeed;
	m_unitScaler = 100;
	m_distance = 20;
	m_enabled = true;
}

Wander::~Wander()
{
}

void Wander::start()
{
}

void Wander::update(float deltaTime)
{
	if (m_enabled)
	{
		m_owner->addForce(getDestination() * deltaTime);
		m_owner->getTransform()->translate(m_owner->getVelocity() * deltaTime);
		m_owner->getTransform()->setRotation(-atan2(m_owner->getVelocity().y, m_owner->getVelocity().x));
	}
}

void Wander::end()
{
}

MathLibrary::Vector2 Wander::getDestination()
{
	srand(time(0));
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution<> distrib(-10, 10);
	float randX = distrib(gen);
	float randY = distrib(gen);
	MathLibrary::Vector2 randpoint = ((MathLibrary::Vector2(randX, randY).getNormalized() * m_unitScaler) + m_owner->getTransform()->getWorldPosition()) + (m_owner->getTransform()->getForward() * m_distance);
	return getSteeringForceTo(randpoint);
}

