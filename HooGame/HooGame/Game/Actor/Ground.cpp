#include "Ground.h"
#include "Engine/Engine.h"
#include "Physics/Physics.h"

Ground::Ground(const Vector2& position) : super("M", position, Color::Green)
{
	myLayer = CollisionLayer::Ground;
	targetLayer = CollisionLayer::None;


	auto* physics = Engine::Get().GetPhysics();

	if (physics != nullptr)
	{
		physics->StartGravity(this);
	}

}
