#pragma once

#include "raymath.h"
#include "Selector.h"
#include "Sequence.h"
#include "Agent.h"
#include "Transform2D.h"
#include "Evade.h"
#include "Seek.h"
#include "Arrival.h"

class MouseCloseCondition : public BehaviourTree
{
public:
	virtual Status update(Agent* agent, float deltaTime)
	{
		MathLibrary::Vector2 mouse = { GetMousePosition().x,GetMousePosition().y };
		// distance = magnitude of (mouse - position)
		float distance = (mouse - agent->getTransform()->getWorldPosition()).getMagnitude();
		if (distance <= 100)
			return BH_SUCCESS;

		return BH_FAILURE;
	}
};

class AttackAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		Seek* seek = agent->GetComponent<Seek>();
		seek->disable();
		Arrival* arrive = agent->GetComponent<Arrival>();
		arrive->enable();
		
		
		return BH_SUCCESS;
	}
};

class StopAttackAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		
		return BH_SUCCESS;
	}
};

class SeekAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		Seek* seek = agent->GetComponent<Seek>();
		seek->enable();
		Arrival* arrive = agent->GetComponent<Arrival>();
		arrive->disable();
		//MathLibrary::Vector2 mouse = { GetMousePosition().x , GetMousePosition().y };
		//MathLibrary::Vector2 direction = mouse - agent->getTransform()->getWorldPosition();

		//// acceleration = direction normal * max speed * dt
		//agent->addForce(direction.getNormalized() * agent->getMaxSpeed() * deltaTime);
		//agent->getTransform()->setRotation(-atan2(mouse.y - agent->getTransform()->getWorldPosition().y, mouse.x - agent->getTransform()->getWorldPosition().x));

		return BH_SUCCESS;
	}
};