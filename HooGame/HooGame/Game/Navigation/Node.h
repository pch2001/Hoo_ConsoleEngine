#pragma once

class Position
{
public :
	int x = 0;
	int y = 0;
	Position(int x, int y) : x(x), y(y){}
};

class Node
{
public :
	Node(int x, int y, Node* parentNode = nullptr) : position(x, y), parentNode(parentNode){}

	Position operator- (const Node& other)
	{
		return Position(position.x - other.position.x, position.y - other.position.y);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x && position.y == other.position.y;
	}


public :
	Position position;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parentNode = nullptr;
};