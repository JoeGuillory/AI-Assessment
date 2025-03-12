#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

namespace Pathfinding {
	struct Node;

	struct Edge {
		Edge() { target = nullptr; cost = 0; }
		Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

		Node* target;
		float cost;
	};

	struct Node {

		Node() {}
		Node(float x, float y) { position.x = x; position.y = y; gScore = 0; previous = nullptr; }

		Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		Node* previous;

		std::vector<Edge> connections;
		void SetSelected(bool value) { selected = value; }
		void ConnectTo(Node* other, float cost);
	private:
		bool selected;
	};

	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	std::vector<Node*> AStar(Node* startNode, Node* endNode);
	float Heuristic(Node* target, Node* endnode);
	void DrawPath(std::vector<Node*>& path, Color lineColor);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, std::vector<Node*>* drawnList);
}