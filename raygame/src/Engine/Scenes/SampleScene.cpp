#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "Input.h"
#include "Agent.h"
#include "CircleCollider.h"
void SampleScene::start()
{
	//This is a better comment
	Actor* test = new Actor(50, 50, "Test");
	test->setCollider(new CircleCollider(20, test));
	Agent* agenttest = new Agent();
	agenttest->AddComponent(new SpriteComponent(agenttest, "Images/enemy.png"));
	agenttest->getTransform()->setScale({ 50, 50 });
	agenttest->getTransform()->setLocalPosition({ 100,100 });
	agenttest->setTarget(test);
	SpriteComponent* sprite = nullptr;
	test->AddComponent(new SpriteComponent(test, "Images/player.png"));
	sprite = test->GetComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });
	test->AddComponent(new Input(test));
	addActor(test);
	addActor(agenttest);
}
