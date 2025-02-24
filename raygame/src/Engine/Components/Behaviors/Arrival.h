#pragma once
#include "Behavior.h"

class Arrival : public Behavior
{
public:
	Arrival();
	Arrival(Actor* owner, Actor* target, float maxspeed, float weight);
	~Arrival();

	void start();
	void update(float deltaTime);
	void end();

	void setRadius(float radius) { m_radius = radius; }
	float getRadius() { return m_radius; }
private:
	float m_radius;
};