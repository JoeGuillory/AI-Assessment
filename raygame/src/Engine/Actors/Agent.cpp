#include "Agent.h"
#include "Transform2D.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"
#include "Persue.h"
#include "Evade.h"
#include "CircleCollider.h"
#include "raylib.h"
#include "raymath.h"

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
	auto seek = AddComponent<Seek>(new Seek(this, m_target, m_maxSpeed, 1));
	auto evade = AddComponent<Evade>(new Evade(this, m_target, m_maxSpeed, 1));
	auto persue = AddComponent<Persue>(new Persue(this, m_target, m_maxSpeed, 1));
	auto wander = AddComponent<Wander>(new Wander(this,m_maxSpeed));
	auto flee = AddComponent<Flee>(new Flee(this, m_target, m_maxSpeed, 1));
	flee->disable();
	seek->disable();
	wander->disable();
	persue->disable();
}

void Agent::update(float deltaTime)
{
	Actor::update(deltaTime);
}

void Agent::end()
{
	Actor::end();
}
