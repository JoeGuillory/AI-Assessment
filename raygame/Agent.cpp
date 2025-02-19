#include "Agent.h"
#include "Transform2D.h"
#include "SeekComponent.h"
#include "FleeComponent.h"
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
	auto seek = AddComponent<SeekComponent>(new SeekComponent(this, m_target, m_maxSpeed));
	auto flee = AddComponent<FleeComponent>(new FleeComponent(this, m_target, m_maxSpeed));
	seek->disable();
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

}

void Agent::end()
{
	Actor::end();
}
