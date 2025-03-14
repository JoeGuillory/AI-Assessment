#pragma once
#include "Scene.h"
class Actor;
class Agent;
class BehaviorDemo : public Scene
{
public:

	void start() override;
	void update(float deltaTime) override;
	void end() override;
};