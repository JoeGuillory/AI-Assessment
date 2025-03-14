#pragma once

#include "raymath.h"
#include "Selector.h"
#include "Sequence.h"
#include "Agent.h"
#include "Transform2D.h"

class MouseCloseCondition : public BehaviourTree
{
public:
	virtual Status update(Agent* agent, float deltaTime)
	{
		MathLibrary::Vector2 mouse = { GetMousePosition().x,GetMousePosition().y };
		// distance = magnitude of (mouse - position)
		float distance = (mouse - agent->getTransform()->getWorldPosition()).getMagnitude();
		if (distance <= 50)
			return BH_SUCCESS;

		return BH_FAILURE;
	}
};

class AttackAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		agent->SetAttack(true);
		return BH_SUCCESS;
	}
};

class StopAttackAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		agent->SetAttack(false);
		return BH_SUCCESS;
	}
};

class SeekAction : public BehaviourTree
{
	virtual Status update(Agent* agent, float deltaTime)
	{
		MathLibrary::Vector2 mouse = { GetMousePosition().x , GetMousePosition().y };
		MathLibrary::Vector2 direction = mouse - agent->getTransform()->getWorldPosition();

		// acceleration = direction normal * max speed * dt
		agent->addForce(direction.getNormalized() * agent->GetMaxSpeed() * deltaTime);

		return BH_SUCCESS;
	}
};