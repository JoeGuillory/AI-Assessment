#pragma once
#include "Behavior.h"
#include "Vector2.h"
#include "SelectorEnum.h"
class Seek : public Behavior
{
public:

	Seek();
	Seek(Actor* owner, Actor* target, float maxspeed, float weight);
	Seek(Actor* owner, MathLibrary::Vector2 point, float maxSpeed, float weight);
	~Seek();

	void start();
	void update(float deltaTime);
	void end();
	void updatePoint(MathLibrary::Vector2 point) { m_point = point; }
private:
	MathLibrary::Vector2 m_point;
	SelectorEnum m_selected;
};