#pragma once
#include "Actor.h"
#include "Transform2D.h"
#include "PathFinding.h"
class Wander;
class PathAgent : public Actor
{
public:
	PathAgent();
	~PathAgent();

	void start();
	void update(float deltaTime);
	void end();
	void draw();
	void GoToNode(Pathfinding::Node* node);
	void SetNode(Pathfinding::Node* node);
	void SetSearchType(int type) { searchType = type; }
	void CheckState(float deltaTime);
	void WrapPosition();
	std::vector<Pathfinding::Node*> path;
	int currentIndex;
	Pathfinding::Node* currentNode;
	Wander* m_wander;
	int m_state;
private:

	int searchType;
};
