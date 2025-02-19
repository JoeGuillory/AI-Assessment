#pragma once
#include "Behavior.h"

class Evade : public Behavior
{
public:

	Evade();
	Evade(Actor* owner, Actor* target, float maxspeed, float weight);
	~Evade();

	void start();
	void update(float deltaTime);
	void end();
};
