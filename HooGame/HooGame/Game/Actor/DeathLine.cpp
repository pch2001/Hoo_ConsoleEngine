#include "DeathLine.h"

DeathLine::DeathLine(const Vector2& position) :super("~",position,Color::White)
{
	sortingOrder = 10;
	myLayer = CollisionLayer::path;
	targetLayer = CollisionLayer::Player;
}

DeathLine::~DeathLine()
{
}
