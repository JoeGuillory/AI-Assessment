#pragma once
#include "Scene.h"
#include "NodeMap.h"
class PathAgent;
class Agent;

class DemoScene : public Scene
{
public:
	void start();
	void update(float deltaTime);
	void end();
	void draw();
private:
	Pathfinding::NodeMap m_nodeMap;
	PathAgent* m_pathAgent;
	Agent* m_actor;
	std::string mode;
	bool switched;
};