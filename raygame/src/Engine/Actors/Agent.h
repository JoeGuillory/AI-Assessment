#pragma once
#include "Actor.h"
#include "Vector2.h"
class Seek;
class Flee;
class Arrival;
class Behavior;
class BehaviourTree;

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
	void WrapPosition();
	void SetAttack(bool state) { m_bAtack = state; }

protected:
	BehaviourTree* m_behaviourTree;
	bool m_bAtack;
private:
	Actor* m_target;
	int m_state;
	Seek* seek;
	Flee* flee;
	Arrival* arrive;
	
};