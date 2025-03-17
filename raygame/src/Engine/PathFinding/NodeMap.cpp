#include <iostream>
#include "NodeMap.h"
#include "raylib.h"

namespace Pathfinding
{
	void NodeMap::Initialise(std::vector<std::string> asciiMap)
	{
		
		const char emptySquare = '0';

		// assume all strings are the same length, so we'll size the map according to the number of strings and the length of the first one
		height = asciiMap.size();
		width = asciiMap[0].size();

		nodes = new Node * [width * height];

		// loop over the strings, creating Node entries as we go
		for (int y = 0; y < height; y++)
		{
			std::string& line = asciiMap[y];
			// report to the use that you have a mis-matched string length
			if (line.size() != width)
				std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << width << ")" << std::endl;

			for (int x = 0; x < width; x++)
			{
				// get the x-th character, or return an empty node if the string isn't long enough 
				char tile = x < line.size() ? line[x] : emptySquare;

				// create a node for anything but a '.' character
				// position it in the middle of the cell, hence the +0.5f's
				nodes[x + width * y] = tile == emptySquare ? nullptr : new Node((x+0.5f) * cellSize, (y+0.5f) * cellSize);
			}
		}

		// now loop over the nodes, creating connections between each node and its neighbour to the West and South on the grid
		// this will link up all nodes 
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Node* node = GetNode(x, y);
				if (node)
				{
					// see if there's a node to our west, checking for array overruns first if we're on the west-most edge
					Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
					if (nodeWest)
					{
						node->ConnectTo(nodeWest, 20); // TODO weights
						nodeWest->ConnectTo(node, 20);
					}

					// see if there's a node south of us, checking for array index overruns again
					Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
					if (nodeSouth)
					{
						node->ConnectTo(nodeSouth, 20);
						nodeSouth->ConnectTo(node, 20);
					}

				}
			}
		}
	}

	void NodeMap::Draw(bool drawConnections)
	{
	
		
		Color cellColor = LIME;
		Color otherColor = BEIGE;
		

		// grey lines for node edges
		Color lineColor = BLACK;
		

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Node* node = GetNode(x, y);
				if (node == nullptr)
				{
					// draw a solid block in empty squares without a navigation node
					//DrawTextureEx(grassTexture, { x * cellSize, y * cellSize }, 0, cellSize / 2, WHITE);
					DrawRectangle(x * cellSize, y * cellSize, cellSize - 1, cellSize - 1, cellColor);
				}
				else
				{
					// draw the connections between the node and its neighbours
					for (int i = 0; i < node->connections.size(); i++)
					{
						Node* other = node->connections[i].target;
						DrawLine(node->position.x, node->position.y, other->position.x, other->position.y, lineColor);
						DrawRectangle(x * cellSize, y * cellSize, cellSize - 1, cellSize - 1, otherColor);
					}
				}
			}
		}
	}

	Node* NodeMap::GetClosestNode(Vector2 worldPos)
	{
		int i = worldPos.x / cellSize;
		if (i < 0 || i >= width) return nullptr;

		int j = worldPos.y / cellSize;
		if (j < 0 || j >= height) return nullptr;

		return GetNode(i, j);
	}
}



