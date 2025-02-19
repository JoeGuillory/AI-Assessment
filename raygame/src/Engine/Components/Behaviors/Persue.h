#pragma once
#include "Behavior.h"

class Persue : public Behavior
{
public:
	Persue();
	Persue(Actor* owner, Actor* target, float maxspeed, float weight);
	~Persue();

	void start();
	void update(float deltaTime);
	void end();




};