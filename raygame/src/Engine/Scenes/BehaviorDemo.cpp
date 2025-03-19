#include "BehaviorDemo.h"
#include "Agent.h"
#include "Actor.h"
#include "Input.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "raylib.h"
#include "Engine.h"
#include "OtherAgent.h"
void BehaviorDemo::start()
{
	Scene::start();
	m_test = new Actor(50, 50, "Test");
	m_test->AddComponent(new SpriteComponent(m_test, "Images/player.png"));
	m_test->AddComponent<Input>(new Input(m_test));
	m_test->getTransform()->setScale({ 25, 25 });
	m_enemy = new OtherAgent(m_test);
	


	addActor(m_test);
	addActor(m_enemy);
}

void BehaviorDemo::update(float deltaTime)
{
	Scene::update(deltaTime);
}

void BehaviorDemo::end()
{
	Scene::end();
	removeActor(m_test);
	removeActor(m_enemy);
	delete m_enemy;
	delete m_test;
}
