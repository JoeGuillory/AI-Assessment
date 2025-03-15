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

	m_behaviourTree =
		(new Selector())->add(
			(new Sequence())->add(
				new MouseCloseCondition())->add(
				new AttackAction()))->add(
			(new Sequence())->add(
				new StopAttackAction())->add(
				new SeekAction()));
	getTransform()->setLocalPosition({ 100,100 });

	/*
	auto evade = AddComponent<Evade>(new Evade(this, m_target, m_maxSpeed, 1));
	auto persue = AddComponent<Persue>(new Persue(this, m_target, m_maxSpeed, 1));
	auto wander = AddComponent<Wander>(new Wander(this,m_maxSpeed,1));
	wander->setScaler(100);
	wander->setDistance(5);
	seek = AddComponent<Seek>(new Seek(this, m_target, m_maxSpeed, 1));
	flee = AddComponent<Flee>(new Flee(this, m_target, m_maxSpeed, 1));
	arrive = AddComponent<Arrival>(new Arrival(this, m_target, m_maxSpeed, 1));
	m_state = STATE_SEEK;
	arrive->setRadius(225);
	persue->disable();
	evade->disable();
	wander->setWeight(0);
	seek->setWeight(1);
	flee->setWeight(0);
	arrive->setWeight(0);*/
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);
	if(m_behaviourTree != nullptr)
		m_behaviourTree->tick(this, deltaTime);
	getTransform()->translate(getVelocity() * deltaTime);
	
	DrawText(std::to_string(getVelocity().x).c_str(),60,60,10,WHITE);
	DrawText(std::to_string(getVelocity().y).c_str(),60,80,10,WHITE);
	DrawText(std::to_string(GetMousePosition().x).c_str(),120,60,10,WHITE);
	DrawText(std::to_string(GetMousePosition().y).c_str(),120,80,10,WHITE);
	
	//CheckState();
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
