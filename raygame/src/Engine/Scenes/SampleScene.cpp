#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "Input.h"
#include "Agent.h"
#include "CircleCollider.h"
#include "PathFinding.h"

void SampleScene::start()
{
	/*
	Actor* test = new Actor(50, 50, "Test");
	test->setCollider(new CircleCollider(20, test));
	Agent* agenttest = new Agent();
	agenttest->AddComponent(new SpriteComponent(agenttest, "Images/enemy.png"));
	agenttest->getTransform()->setScale({ 50, 50 });
	agenttest->getTransform()->setLocalPosition({ 300,400 });
	agenttest->setTarget(test);
	SpriteComponent* sprite = nullptr;
	test->AddComponent(new SpriteComponent(test, "Images/player.png"));
	sprite = test->GetComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });
	test->AddComponent(new Input(test));
	addActor(test);
	addActor(agenttest);*/
}

void SampleScene::update(float deltaTime)
{
	Pathfinding::Node a(500,500);
	Pathfinding::Node b(600,400);
	Pathfinding::Node c(600,600);

	a.ConnectTo(&b, 1);
	a.ConnectTo(&c, 4);

	/*List<Pathfinding::Node*> path = { &a,&b,&c };

	Pathfinding::DrawPath(path, RED);
	Pathfinding::DrawNode(&a);*/
	List<Pathfinding::Node*> list;
	Pathfinding::DrawGraph(&a, &list);

}
