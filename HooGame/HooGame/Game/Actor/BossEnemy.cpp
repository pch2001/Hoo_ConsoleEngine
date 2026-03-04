#include "BossEnemy.h"
#include "Engine/Engine.h"
#include "PlayerAttack.h"
#include "Effect/Effect.h"

BossEnemy::BossEnemy() : super("B", Vector2(Engine::Get().GetWidth()/2, Engine::Get().GetHeight()/2 ), Color::Red)
{
	sortingOrder = 8;

	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Tick(float deltaTime)
{
}

void BossEnemy::OnOverlap(Actor* actor)
{
}
void BossEnemy::MisileAttack()
{
	//GetOwner()->AddNewActor(new Effect(this->GetPosition(), this, 1.f));

	//AddNewActor(new Effect(this->GetPosition(), this, 1.f));
}
