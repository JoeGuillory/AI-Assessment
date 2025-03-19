#pragma once
#include "Scene.h"
class Actor;
class OtherAgent;
class BehaviorDemo : public Scene
{
public:

	void start() override;
	void update(float deltaTime) override;
	void end() override;

	Actor* m_test;
	OtherAgent* m_enemy;
};