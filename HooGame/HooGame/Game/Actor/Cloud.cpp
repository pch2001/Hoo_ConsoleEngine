#include "Cloud.h"
#include "Engine/Engine.h"
#include "Physics/Physics.h"



Cloud::Cloud(const Vector2& position) : super("O",position, Color::Blue)
{
	//myLayer = CollisionLayer::None;
	//targetLayer = CollisionLayer::None;

	sortingOrder = 0;
	
}

Cloud::~Cloud()
{
}
