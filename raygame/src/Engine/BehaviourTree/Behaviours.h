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
		if (distance <= 25)
			return BH_SUCCESS;

		Arrival* arrive = agent->GetComponent<Arrival>();
		arrive->disable();
		return BH_FAILURE;

	}
};

class ArriveAction : public BehaviourTree
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
		return BH_SUCCESS;
	}
};

class TargetNotClose : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		float distance = (agent->getTarget()->getTransform()->getWorldPosition() - agent->getTransform()->getWorldPosition()).getMagnitude();
		if (distance > 100)
			return BH_SUCCESS;

		return BH_FAILURE;
	}
};
class TargetClose : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		float distance = (agent->getTarget()->getTransform()->getWorldPosition() - agent->getTransform()->getWorldPosition()).getMagnitude();
		if (distance < 100)
			return BH_SUCCESS;

		Evade* evade = agent->GetComponent<Evade>();
		evade->disable();
		return BH_FAILURE;
	}
};

class EvadeTarget : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		Seek* seek = agent->GetComponent<Seek>();
		seek->disable();
		Evade* evade = agent->GetComponent<Evade>();
		evade->enable();

		return BH_SUCCESS;
	}
};