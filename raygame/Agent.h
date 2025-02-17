#pragma once
#include "Actor.h"
#include "Vector2.h"
class Agent : public Actor
{
public:
	Agent();
	~Agent();

	void start();
	void update(float deltaTime);
	void end();
	
private:
	
	
};