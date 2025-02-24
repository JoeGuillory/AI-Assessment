#include "Agent.h"
#include "Transform2D.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"
#include "Persue.h"
#include "Evade.h"
#include "Arrival.h"
#include "CircleCollider.h"
#include "raylib.h"
#include "raymath.h"

enum AIState
{
	STATE_SEEK = 0,
	STATE_ARRIVE,
	STATE_FLEE
};

Agent::Agent() : Actor::Actor()
{
}


Agent::Agent(Actor* target) : Actor::Actor()
{
	m_target = target;
}


Agent::~Agent()
{
}

void Agent::start()
{
	Actor::start();
	m_maxSpeed = 200;
	setMaxVelocity({ m_maxSpeed,m_maxSpeed });
	auto evade = AddComponent<Evade>(new Evade(this, m_target, m_maxSpeed, 1));
	auto persue = AddComponent<Persue>(new Persue(this, m_target, m_maxSpeed, 1));
	auto wander = AddComponent<Wander>(new Wander(this,m_maxSpeed,1));
	seek = AddComponent<Seek>(new Seek(this, m_target, m_maxSpeed, 1));
	flee = AddComponent<Flee>(new Flee(this, m_target, m_maxSpeed, 1));
	arrive = AddComponent<Arrival>(new Arrival(this, m_target, m_maxSpeed, 1));
	m_state = STATE_SEEK;
	arrive->setRadius(90);
	persue->disable();
	evade->disable();
	wander->disable();
	seek->setWeight(1);
	flee->setWeight(0);
	arrive->setWeight(0);
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);
	CheckState();
}

void Agent::end()
{
	Actor::end();
}

void Agent::CheckState()
{
	switch (m_state)
	{
	case STATE_SEEK:
		
		seek->setWeight(1);
		if (m_target->getVelocity().x == 0 || m_target->getVelocity().y == 0)
		{
			float distance = (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getMagnitude();
			if (distance < arrive->getRadius())
			{
				seek->setWeight(0);
				m_state = STATE_ARRIVE;
			}
		}
		else if(m_target->getVelocity().x != 0 || m_target->getVelocity().y != 0)
		{
			seek->setWeight(0);
			m_state = STATE_FLEE;
		}
		break;
	case STATE_FLEE:
		flee->setWeight(1);
		if (m_target->getVelocity().x == 0 || m_target->getVelocity().y == 0)
		{
			flee->setWeight(0);
			m_state = STATE_SEEK;
		}
		break;
	case STATE_ARRIVE:
		arrive->setWeight(1);
		if (m_target->getVelocity().x != 0 || m_target->getVelocity().y != 0)
		{
			arrive->setWeight(0);
			m_state = STATE_FLEE;
		}
		break;
	default:
		break;
	}
}
