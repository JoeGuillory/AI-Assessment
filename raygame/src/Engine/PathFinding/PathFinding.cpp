#include "PathFinding.h"
#include <stdio.h>

namespace Pathfinding
{
	bool NodeSort(Node* i, Node* j)
	{
		return (i->gScore < j->gScore);
	}

	void Node::ConnectTo(Node* other, float cost)
	{
		connections.pushBack(Edge(other, cost));
	}

	List<Node*> DijkstrasSearch(Node* startNode, Node* endNode)
	{
		//Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return List<Node*>();
		}

		if (startNode == endNode)
		{
			List<Node*> singleNodePath;
			singleNodePath.pushBack(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		List<Node*> openList;
		List<Node*> closedList;

		//Add the starting node to openList
		openList.pushBack(startNode);


		while (openList.getLength() > 0)
		{
			

			//Set the current node to the first node in the openList
			Node* currentNode = openList.first();
			//Remove currentNode from openList
			openList.popFront();
			//Add currentNode to closedList
			closedList.pushBack(currentNode);

			//If the destination node was added to the closed list,
			//the shortest path has been found
			if (currentNode == endNode)
			{
				break;
			}

			//For each Edge e in currentNode's connections
			for (Edge e : currentNode->connections)
			{
				//If the target node is in the closedList, ignore it
				if (closedList.find(e.target) != closedList.end()) 
				{
					continue;
				}
				//If the target node is not in the openList, update it
				if (openList.find(e.target) == openList.end()) 
				{
					//Calculate the target node's G Score
					e.target->gScore = currentNode->gScore + e.cost;
					//Set the target node's previous to currentNode
					e.target->previous = currentNode;
					//Sort
					int index = 0;
					for (auto i = openList.begin(); i != openList.end(); i++, index++) 
					{
						if (NodeSort(e.target, (*i)))
						{
							break;
						}
					}
					//Insert the node at the appropriate position
					openList.insert(e.target,index);

				}
				//Otherwise the target node IS in the open list
				else 
				{
					//Compare the new G Score to the old one before updating
					if (currentNode->gScore + e.cost < e.target->gScore) 
					{
						//Calculate the target node's G Score
						e.target->gScore = currentNode->gScore + e.cost;
						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		List<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			//Add the current node to the beginning of the path
			path.pushFront(currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}
		return path;
	}

	List<Node*> AStar(Node* startNode, Node* endNode)
	{
		//Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return List<Node*>();
		}

		if (startNode == endNode)
		{
			List<Node*> singleNodePath;
			singleNodePath.pushBack(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->fScore = 0;
		startNode->hScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		List<Node*> openList;
		List<Node*> closedList;

		//Add the starting node to openList
		openList.pushBack(startNode);


		while (openList.getLength() > 0)
		{
			//Set the current node to the first node in the openList
			Node* currentNode = openList.first();
			//Remove currentNode from openList
			openList.popFront();
			//Add currentNode to closedList
			closedList.pushBack(currentNode);

			//If the destination node was added to the closed list,
			//the shortest path has been found
			if (currentNode == endNode)
			{
				break;
			}

			//For each Edge e in currentNode's connections
			for (Edge e : currentNode->connections)
			{
				//If the target node is in the closedList, ignore it
				if (closedList.find(e.target) != closedList.end())
				{
					currentNode->gScore = currentNode->gScore + e.cost;
					currentNode->hScore = Heuristic(e.target, endNode);
					currentNode->fScore = currentNode->gScore + currentNode->hScore;
					continue;
				}
				//If the target node is not in the openList, update it
				if (openList.find(e.target) == openList.end())
				{
					//Calculate the target node's G Score
					e.target->gScore = currentNode->gScore;
					e.target->fScore = currentNode->fScore;
					//Set the target node's previous to currentNode
					e.target->previous = currentNode;
					//Sort then put in the open list
					int index = 0;
					for (auto i = openList.begin(); i != openList.end(); i++, index++)
					{
						if (e.target->fScore < (*i)->fScore)
						{
							break;
						}
					}
					//Insert the node at the appropriate position
					openList.insert(e.target, index);

				}
				//Otherwise the target node IS in the open list
				else
				{
					//Compare the new G Score to the old one before updating
					if (currentNode->gScore + e.cost < e.target->gScore)
					{
						//Calculate the target node's G Score
						e.target->gScore = currentNode->gScore + e.cost;
						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		List<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			//Add the current node to the beginning of the path
			path.pushFront(currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}
		return path;
	}

	float Heuristic(Node* target, Node* endNode)
	{
		return (target->position.x - endNode->position.x) + (target->position.y - endNode->position.y);
	}


	void DrawPath(List<Node*>& path, Color lineColor)
	{
		auto currentIter = path.begin();
		auto previousIter = currentIter;
		currentIter++;
		for (currentIter; currentIter != path.end(); currentIter++, previousIter++)
		{
			DrawLine((*previousIter)->position.x, (*previousIter)->position.y, (*currentIter)->position.x, (*currentIter)->position.y, lineColor);
		}
	}

	void DrawNode(Node* node, bool selected)
	{
		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 25, YELLOW);
		//Draw the inner circle
		if (selected)
		{
			DrawCircle(node->position.x, node->position.y, 22, BROWN);
		}
		else
		{
			DrawCircle(node->position.x, node->position.y, 22, BLACK);
		}
		//Draw the text
		DrawText(buffer, node->position.x - 10, node->position.y - 10, 15, WHITE);
	}

	void DrawGraph(Node* node, List<Node*>* drawnList)
	{
		DrawNode(node);
		drawnList->pushBack(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);
			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			DrawText(buffer, costPos.x, costPos.y, 15, WHITE);
			//Draw the target node
			if (drawnList->find(e.target) == drawnList->end())
			{
				DrawGraph(e.target, drawnList);
			}
		}
	}

}