#pragma once
#include "Scene.h"
#include "NodeMap.h"
class PathAgent;

class DemoScene : public Scene
{
public:
	void start();
	void update(float deltaTime);
	void end();
private:
	Pathfinding::NodeMap m_nodeMap;
	PathAgent* m_pathAgent;
	std::string mode;
	bool switched;
};