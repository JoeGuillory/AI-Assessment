#pragma once
#include "Component.h"
#include "Vector2.h"

class Actor;

class Behavior : public Component
{
public:
	Behavior();
	Behavior(Actor* owner, Actor* target, float maxspeed, float weight);
	~Behavior();

	void start();
	void update(float deltaTime);
	void end();

	void setTarget(Actor* target) { m_target = target; }
	void setWeight(float weight);
	/// <summary>
	/// Get Steering force to the target
	/// </summary>
	/// <returns></returns>
	MathLibrary::Vector2 getSteeringForceTo(MathLibrary::Vector2 otherVelocity = {0,0});
	/// <summary>
	/// Get Steering force from a point
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	MathLibrary::Vector2 getForceToPoint(MathLibrary::Vector2 point);
	/// <summary>
	/// Get Steering force away from the target
	/// </summary>
	/// <returns></returns>
	MathLibrary::Vector2 getSteeringForceAway(MathLibrary::Vector2 otherVelocity = {0,0});
	/// <summary>
	/// Get Steering force away from a point
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	MathLibrary::Vector2 getForceAwayPoint(MathLibrary::Vector2 point);

protected:
	float m_weight;
	Actor* m_target;
	float m_maxSpeed;
};


