#pragma once
#include "Component.h"
class Input : public Component
{
public:
	Input();
	Input(Actor* owner,const char* name = "");
	~Input();

	void start();
	void update(float deltaTime);
	void end();
private:
	float m_speed;
	float m_rotatespeed;

};

