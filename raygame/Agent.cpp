#include "Agent.h"
#include "Transform2D.h"
Agent::Agent() : Actor::Actor()
{
}

Agent::~Agent()
{
}

void Agent::start()
{
	Actor::start();

}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);

}

void Agent::end()
{
	Actor::end();
}
