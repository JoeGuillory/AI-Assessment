#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "Input.h"
#include "Agent.h"
#include "CircleCollider.h"
#include "PathFinding.h"
#include "PathAgent.h"

void SampleScene::start()
{
	m_nodeMap.cellSize = 32;
	std::vector<std::string> asciiMap;
	asciiMap.push_back("000000000000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("011111100000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000111110");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000000000");
	m_nodeMap.Initialise(asciiMap);

	m_pathAgent = new PathAgent();
	addActor(m_pathAgent);
	m_pathAgent->SetNode(m_nodeMap.GetNode(1,1));
	m_pathAgent->speed = 64;

}

void SampleScene::update(float deltaTime)
{
	Scene::update(deltaTime);

	bool drawNodeMap = true;
	Color lineColor = { 255, 255, 255, 255 };

	m_nodeMap.Draw(true);
	Pathfinding::DrawPath(m_pathAgent->path, lineColor);

	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		Pathfinding::Node* end = m_nodeMap.GetClosestNode(mousePos);
		m_pathAgent->SetSearchType(2);
		m_pathAgent->GoToNode(end);
	}
	
}

void SampleScene::end()
{
	delete m_pathAgent;
}
