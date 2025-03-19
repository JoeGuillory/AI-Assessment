#pragma once
#include "Actor.h"
class Flee;
class Persue;


class OtherAgent : public Actor
{
public:
	OtherAgent();
	OtherAgent(Actor* target);
	~OtherAgent();

	void start();
	void update(float deltaTime);
	void end();
	void setTarget(Actor* actor) { m_target = actor; }
	Actor* getTarget() { return m_target; }
	void CheckState();
	void WrapPosition();
	float distanceToTarget();

private:
	Actor* m_target;
	int m_state;
	Flee* m_flee;
	Persue* m_persue;
};