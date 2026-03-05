#pragma once

#include "Node.h"
#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

class Astar
{
	struct Direction
	{
		int x = 0;
		int y = 0;
		float cost = 0.0f;
	};

public :
	Astar();
	~Astar();

	std::vector<Node*> FindPath(Node* StartNode, Node* goalNode, std::vector<std::vector<int>>& grid);
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

private :
	std::vector<Node*> ConstructPath(Node* goalNode);
	float CalculateHeuristic(Node* currentNode, Node* goalNode);
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);
	bool HasVisited(int x, int y, float gCost);
	bool IsDestination(const Node* const node);
	void DisplayGrid(std::vector<std::vector<int>>& grid);

private :
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	Node* neighborNode = nullptr;
};

