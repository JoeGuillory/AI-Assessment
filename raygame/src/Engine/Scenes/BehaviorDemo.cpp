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
	Actor* test = new Actor(50, 50, "Test");
	test->AddComponent(new SpriteComponent(test, "Images/player.png"));
	test->AddComponent<Input>(new Input(test));
	test->getTransform()->setScale({ 25, 25 });
	OtherAgent* enemy = new OtherAgent(test);
	


	addActor(test);
	addActor(enemy);
}

void BehaviorDemo::update(float deltaTime)
{
	Scene::update(deltaTime);
}

void BehaviorDemo::end()
{
	Scene::end();
}
