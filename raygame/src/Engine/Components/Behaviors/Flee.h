#pragma once
#include "Behavior.h"

class Flee : public Behavior
{
public:

	Flee();
	Flee(Actor* owner, Actor* target, float maxSpeed, float weight);
	~Flee();

	void start();
	void update(float deltaTime);
	void end();




};
