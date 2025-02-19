#pragma once
#include "Actor.h"
#include "Vector2.h"
class Agent : public Actor
{
public:
	Agent();
	Agent(Actor* target);
	~Agent();

	void start();
	void update(float deltaTime);
	void end();
	void setTarget(Actor* actor) { m_target = actor; }
private:
	Actor* m_target;
	float m_maxSpeed;
	
};