#pragma once
#include "Behavior.h"
#include "Vector2.h"
class Wander : public Behavior
{
public:

	Wander();
	Wander(Actor* owner, float maxspeed, float weight);
	~Wander();

	void start();
	void update(float deltaTime);
	void end();
	void setDistance(float distance) { m_distance = distance; }
	/// <summary>
	/// Returns a Steering force of the next Random position
	/// </summary>
	/// <returns></returns>
	MathLibrary::Vector2 getDestination();

private:
	float m_distance;
	float m_unitScaler;
};