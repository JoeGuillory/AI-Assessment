#include "Input.h"
#include "Actor.h"
#include "raylib.h"
#include "Transform2D.h"

Input::Input()
{
	
}

Input::Input(Actor* owner, const char* name) : Component::Component(owner,name)
{
	m_speed = 100;
	m_rotatespeed = 5;
}

Input::~Input()
{
}

void Input::start()
{
}

void Input::update(float deltaTime)
{
	if (IsKeyDown(KEY_W))
	{
		getOwner()->getTransform()->translate(getOwner()->getTransform()->getForward() * m_speed * deltaTime);
	}

	if(IsKeyDown(KEY_S))
	{
		getOwner()->getTransform()->translate(getOwner()->getTransform()->getForward() * -m_speed * deltaTime);
	}
	
	if (IsKeyDown(KEY_A))
	{
		getOwner()->getTransform()->rotate(m_rotatespeed * deltaTime);
	}

	if (IsKeyDown(KEY_D))
	{
		getOwner()->getTransform()->rotate(-m_rotatespeed * deltaTime);
	}
}

void Input::end()
{
}
