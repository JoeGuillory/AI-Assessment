#include "Agent.h"
#include "Transform2D.h"
#include "SeekComponent.h"
Agent::Agent() : Actor::Actor()
{
}


Agent::Agent(Actor* target) : Actor::Actor()
{
	m_target = target;
}

Agent::~Agent()
{
}

void Agent::start()
{
	Actor::start();
	m_maxSpeed = 100;
	AddComponent<SeekComponent>(new SeekComponent(this, m_target, m_maxSpeed));
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

}

void Agent::end()
{
	Actor::end();
}
