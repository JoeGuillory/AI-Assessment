#pragma once
#include "Component.h"
class FleeComponent : public Component
{
public:
	FleeComponent();
	FleeComponent(Actor* owner, Actor* target, float maxspeed);
	~FleeComponent();


	void start();
	void update(float deltaTime);
	void end();
	void setTarget(Actor* target) { m_target = target; }
private:
	Actor* m_target;
	float m_maxSpeed;

};