#pragma once
#include "Behavior.h"

class Seek : public Behavior
{
public:

	Seek();
	Seek(Actor* owner, Actor* target, float maxspeed, float weight);
	~Seek();

	void start();
	void update(float deltaTime);
	void end();
};