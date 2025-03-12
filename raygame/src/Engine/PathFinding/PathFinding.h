#pragma once
#include "raylib.h"
#include "List.h"

namespace Pathfinding
{
	struct Node;

	struct Edge
	{
		Edge() : target(nullptr), cost(1) {}
		Edge(Node* target, float cost) : target(target), cost(cost) {}

		Node* target;
		float cost;
	};

	struct Node
	{
		Node() : position(Vector2()), gScore(0), hScore(0),fScore(0), previous(nullptr), connections(List<Edge>()) {}
		Node(float x, float y) : position({x,y}), gScore(0), hScore(0), fScore(0), previous(nullptr), connections(List<Edge>()) {}

		Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		Node* previous;

		List<Edge> connections;

		void ConnectTo(Node* other, float cost);
	};

	List<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	List<Node*> AStar(Node* startNode, Node* endNode);
	float Heuristic(Node* target, Node* endNode);
	void DrawPath(List<Node*>& path, Color lineColor);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, List<Node*>* drawnList);

}