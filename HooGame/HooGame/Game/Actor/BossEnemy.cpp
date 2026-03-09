#include "BossEnemy.h"
#include "Engine/Engine.h"
#include "PlayerAttack.h"
#include "Effect/Effect.h"
#include "Level/BossLevel.h"
#include "Effect/guidedMissile.h"

#include "Core/Input.h"
//#include "Game/Game.h"
#include "Render/Renderer.h"
BossEnemy::BossEnemy() : super("I", Vector2(Engine::Get().GetWidth()/2, Engine::Get().GetHeight()/2 ), Color::Red)
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
	super::Tick(deltaTime);

	if (boomCount < 0)
		return;

	attackTimer.Tick(deltaTime);
	if (attackTimer.IsTimeOut())
	{
		StartAttack();
		attackTimer.Reset();
	}

	if (Input::Get().GetKeyDown('p') || Input::Get().GetKeyDown('P')) {
		MisileAttack();
	}
}

void BossEnemy::OnOverlap(Actor* actor)
{
}

void BossEnemy::SetAttackCountUI(int boomcount)
{
	SetboomCount(boomcount*10);
	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	currentLevel->boomCount = std::to_string(boomcount*10);
}

void BossEnemy::StartAttack()
{
	GetOwner()->AddNewActor(new Effect(this->GetPosition(), this, 1.f));
	SetboomCount(-1);
}

void BossEnemy::MisileAttack()
{
	GetOwner()->AddNewActor(new Effect(this->GetPosition(), this, 1.f));
}
