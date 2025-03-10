#pragma once
#include "PathFinding.h"
#include <string>

namespace Pathfinding
{
	class NodeMap
	{
	public:
		int width, height;
		float cellSize;

		Node** nodes;

		void Initialise(List<std::string> asciiMap);
		void Draw(bool drawConnections);

		// utility functions 
		Node* GetNode(int x, int y) { return nodes[x + width * y]; }
		Node* GetClosestNode(Vector2 worldPos);
	};
}