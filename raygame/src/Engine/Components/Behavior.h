#pragma once
#include "Component.h"
#include "Vector2.h"

class Actor;

class Behavior : public Component
{
public:
	Behavior();
	Behavior(Actor* owner, Actor* target, float maxspeed, float weight);
	~Behavior();

	void start();
	void update(float deltaTime);
	void end();

	void setTarget(Actor* target) { m_target = target; }
	void setWeight(float weight);

	MathLibrary::Vector2 SeekForce();
	MathLibrary::Vector2 FleeForce();
	MathLibrary::Vector2 PursueForce();
	MathLibrary::Vector2 EvadeForce();
	MathLibrary::Vector2 ArriveForce();
	MathLibrary::Vector2 SeekForcePoint(MathLibrary::Vector2 point);

protected:
	float m_weight;
	Actor* m_target;
	float m_maxSpeed;
};


