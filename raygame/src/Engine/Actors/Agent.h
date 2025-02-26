#pragma once
#include "Actor.h"
#include "Vector2.h"
class Seek;
class Flee;
class Arrival;
class Behavior;

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
	void CheckState();

private:
	Actor* m_target;
	float m_maxSpeed;
	int m_state;
	Seek* seek;
	Flee* flee;
	Arrival* arrive;
	
};