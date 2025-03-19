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
#include "SpriteComponent.h"
#include "BehaviourTree.h"
#include "Behaviours.h"
#include <string>
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
	if (m_behaviourTree != nullptr)
		delete m_behaviourTree;
}

void Agent::start()
{
	Actor::start();
	m_bAtack = false;
	setMaxSpeed(400);
	AddComponent<SpriteComponent>(new SpriteComponent(this, "Images/enemy.png"));
	m_seek = AddComponent<Seek>(new Seek(this, {GetMousePosition().x,GetMousePosition().y}, getMaxSpeed(), 1));
	m_arrive = AddComponent<Arrival>(new Arrival(this, { GetMousePosition().x,GetMousePosition().y }, getMaxSpeed(), 1));
	m_arrive->disable();
	m_arrive->setRadius(100);
	getTransform()->scale({ 20,20 });
	m_behaviourTree =
		(new Selector())->add(
			(new Sequence())->add(
				new MouseCloseCondition())->add(
				new ArriveAction()))->add(
			(new Sequence())->add(
				new StopAttackAction())->add(
				new SeekAction()));
	getTransform()->setLocalPosition({ 100,100 });

}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);
	m_seek->updatePoint({ GetMousePosition().x,GetMousePosition().y });
	m_arrive->updatePoint({ GetMousePosition().x,GetMousePosition().y });
	if(m_behaviourTree != nullptr)
		m_behaviourTree->tick(this, deltaTime);
	getTransform()->translate(getVelocity() * deltaTime);
	
	
	WrapPosition();
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
		
		m_seek->setWeight(1);
		if (m_target->getVelocity().x == 0 || m_target->getVelocity().y == 0)
		{
			float distance = (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getMagnitude();
			if (distance < m_arrive->getRadius())
			{
				m_seek->setWeight(0);
				m_state = STATE_ARRIVE;
			}
		}
		else if(m_target->getVelocity().x != 0 || m_target->getVelocity().y != 0)
		{
			m_seek->setWeight(0);
			m_state = STATE_FLEE;
		}
		break;
	case STATE_FLEE:
		m_flee->setWeight(1);
		if (m_target->getVelocity().x == 0 || m_target->getVelocity().y == 0)
		{
			m_flee->setWeight(0);
			m_state = STATE_SEEK;
		}
		break;
	case STATE_ARRIVE:
		m_arrive->setWeight(1);
		if (m_target->getVelocity().x != 0 || m_target->getVelocity().y != 0)
		{
			m_arrive->setWeight(0);
			m_state = STATE_FLEE;
		}
		break;
	default:
		break;
	}
}

void Agent::WrapPosition()
{
	float xpos = getTransform()->getWorldPosition().x;
	float ypos = getTransform()->getWorldPosition().y;


	if (xpos < 0)
	{
		getTransform()->setLocalPosition({ (float)GetScreenWidth(),ypos });
	}

	if (xpos > GetScreenWidth())
	{
		getTransform()->setLocalPosition({ 0,ypos });
	}

	if (ypos < 0)
	{
		getTransform()->setLocalPosition({xpos,(float)GetScreenHeight()});
	}

	if (ypos > GetScreenHeight())
	{
		getTransform()->setLocalPosition({xpos, 0});
	}

}
