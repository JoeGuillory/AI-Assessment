#include "DemoScene.h"
#include "PathAgent.h"

void DemoScene::start()
{
	Scene::start();
	m_nodeMap.cellSize = 32;
	std::vector<std::string> asciiMap;
	asciiMap.push_back("000000000000000000000000000000000000000000000");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111110000011111111111111111110");
	asciiMap.push_back("011111111111111111111111111111111111111111110");
	asciiMap.push_back("011111111111111111111111111111111111111111110");
	asciiMap.push_back("000000000000000000000000000000000000000000000");
	m_nodeMap.Initialise(asciiMap);

	m_pathAgent = new PathAgent();
	addActor(m_pathAgent);
	m_pathAgent->SetNode(m_nodeMap.GetNode(1, 1));
	m_pathAgent->speed = 200;
}

void DemoScene::update(float deltaTime)
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
		m_pathAgent->GoToNode(end);
	}
	
	if (IsKeyPressed(KEY_SPACE))
	{
		
		if (switched == false)
		{
			m_pathAgent->SetSearchType(2);
			switched = true;
			mode.clear();
			mode.assign("Astar");
		}
		else if(switched == true)
		{
			m_pathAgent->SetSearchType(1);
			switched = false;
			mode.clear();
			mode.assign("DijkstrasSearch");
		}
	}
	DrawText(mode.c_str(), 600, 600, 30, WHITE);
}

void DemoScene::end()
{
	Scene::end();
}
