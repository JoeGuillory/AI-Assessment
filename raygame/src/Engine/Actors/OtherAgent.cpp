#include "OtherAgent.h"
#include "Transform2D.h"
#include "raylib.h"
#include "Flee.h"
#include "Persue.h"
#include "SpriteComponent.h"

OtherAgent::OtherAgent()
{
}

OtherAgent::OtherAgent(Actor* target) : m_target(target)
{
	
}

OtherAgent::~OtherAgent()
{
}

void OtherAgent::start()
{
	Actor::start();
	AddComponent<SpriteComponent>(new SpriteComponent(this, "Images/enemy.png"));
	getTransform()->setScale({ 25,25 });
	setMaxSpeed(180);
	m_flee = AddComponent<Flee>(new Flee(this, m_target, getMaxSpeed(), 1));
	m_flee->disable();
	m_persue = AddComponent<Persue>(new Persue(this, m_target, getMaxSpeed(), 1));
}

void OtherAgent::update(float deltaTime)
{
	Actor::update(deltaTime);
	if (distanceToTarget() > 100)
	{
		m_persue->enable();
		m_flee->disable();
	}
	else
	{
		m_persue->disable();
		m_flee->enable();
	}
	

	WrapPosition();
}

void OtherAgent::end()
{
	Actor::end();
}

void OtherAgent::CheckState()
{
}

void OtherAgent::WrapPosition()
{
	float xpos = getTransform()->getWorldPosition().x;
	float ypos = getTransform()->getWorldPosition().y;


	if (xpos < 0)
	{
		getTransform()->setLocalPosition({ (float)GetScreenWidth(),ypos });
	}

	if (xpos > GetScreenWidth())
	{
		getTransform()->setLocalPosition({ 0,ypos });
	}

	if (ypos < 0)
	{
		getTransform()->setLocalPosition({ xpos,(float)GetScreenHeight() });
	}

	if (ypos > GetScreenHeight())
	{
		getTransform()->setLocalPosition({ xpos, 0 });
	}

}

float OtherAgent::distanceToTarget()
{
	if (m_target)
	{
		return (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getMagnitude();
	}
	return 0;
}
