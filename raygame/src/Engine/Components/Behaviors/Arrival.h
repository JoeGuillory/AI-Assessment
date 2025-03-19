#pragma once
#include "Behavior.h"
#include "SelectorEnum.h"

class Arrival : public Behavior
{
public:
	Arrival();
	Arrival(Actor* owner, Actor* target, float maxspeed, float weight);
	Arrival(Actor* owner, MathLibrary::Vector2 point, float maxspeed, float weight);
	~Arrival();

	void start();
	void update(float deltaTime);
	void end();

	void setRadius(float radius) { m_radius = radius; }
	float getRadius() { return m_radius; }
	void updatePoint(MathLibrary::Vector2 point) {m_point = point; }
private:
	float m_radius;
	MathLibrary::Vector2 m_point;
	SelectorEnum m_selected;
	
};