#include "Input.h"
#include "Actor.h"
#include "raylib.h"
#include "Transform2D.h"

Input::Input()
{
	
}

Input::Input(Actor* owner, const char* name) : Component::Component(owner,name)
{
	m_speed = 250;
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
		m_owner->addForce(getOwner()->getTransform()->getForward() * m_speed );
		getOwner()->getTransform()->translate(m_owner->getVelocity()  * deltaTime);
	}

	if(IsKeyDown(KEY_S))
	{
		m_owner->addForce(getOwner()->getTransform()->getForward() * -m_speed);
		getOwner()->getTransform()->translate(m_owner->getVelocity()  * deltaTime);
	}
	
	if (IsKeyDown(KEY_A))
	{
		getOwner()->getTransform()->rotate(m_rotatespeed * deltaTime);
	}

	if (IsKeyDown(KEY_D))
	{
		getOwner()->getTransform()->rotate(-m_rotatespeed * deltaTime);
	}
	WrapPosition();
}

void Input::end()
{
}

void Input::WrapPosition()
{
	float xpos = getOwner()->getTransform()->getWorldPosition().x;
	float ypos = getOwner()->getTransform()->getWorldPosition().y;


	if (xpos < 0)
	{
		getOwner()->getTransform()->setLocalPosition({ (float)GetScreenWidth(),ypos });
	}

	if (xpos > GetScreenWidth())
	{
		getOwner()->getTransform()->setLocalPosition({ 0,ypos });
	}

	if (ypos < 0)
	{
		getOwner()->getTransform()->setLocalPosition({ xpos,(float)GetScreenHeight() });
	}

	if (ypos > GetScreenHeight())
	{
		getOwner()->getTransform()->setLocalPosition({ xpos, 0 });
	}







}
