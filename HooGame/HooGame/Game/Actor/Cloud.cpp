#include "Cloud.h"
#include "Engine/Engine.h"
#include "Physics/Physics.h"



Cloud::Cloud(const Vector2& position) : super("O",position, Color::Blue)
{
	myLayer = CollisionLayer::Cloud;
	targetLayer = CollisionLayer::None;

	sortingOrder = 0;

	auto* physics = Engine::Get().GetPhysics();

	if (physics != nullptr)
	{
		physics->StartGravity(this);
	}

}

Cloud::~Cloud()
{
}
