#pragma once
#include "Component.h"
#include "Vector2.h"
class Actor;

class SeekComponent : public Component
{
public:

	SeekComponent();
	SeekComponent(Actor* owner, Actor* target, float maxspeed);
	~SeekComponent();

	void start();
	void update(float deltaTime);
	void end();
	void setTarget(Actor* target) { m_target = target; }
private:
	Actor* m_target;
	float m_maxSpeed;
};