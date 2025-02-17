#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "Input.h"
void SampleScene::start()
{
	//This is a better comment
	Actor* test = new Actor(50, 50, "Test");
	SpriteComponent* sprite = nullptr;
	test->AddComponent(new SpriteComponent(test, "Images/player.png"));
	sprite = test->GetComponent(sprite);
	test->getTransform()->setScale({ 50, 50 });
	test->AddComponent(new Input(test));
	addActor(test);
}
