#include "Item.h"
#include "Player.h"

Item::Item(const Vector2& position) : super("Item", position, Color::Blue)
{
	sortingOrder = 7;
	myLayer = CollisionLayer::None;
	targetLayer = CollisionLayer::Player;
}

Item::~Item()
{
}

void Item::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<Player>())
	{
		Player* tempactor = static_cast<Player*>(actor);
		if (tempactor)
		{
			tempactor->Upgrade();
		}
	}
	this->Destroy();
}
