#include "Hyeonmu5.h"
#include "Level/BossLevel.h"
#include "Engine/Engine.h"

// Todo :: 현무 추가필요

Hyeonmu5::Hyeonmu5(const Vector2& position) : super("H", position, Color::Brown, false)
{
	sortingOrder = 10;
	myLayer = CollisionLayer::PlayerAttack;
	targetLayer = CollisionLayer::Enemy;
	
}

Hyeonmu5::~Hyeonmu5()
{
}
