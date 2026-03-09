#include "BossEnemy.h"
#include "Engine/Engine.h"
#include "PlayerAttack.h"
#include "Effect/Effect.h"
#include "Level/BossLevel.h"
#include "Effect/guidedMissile.h"

#include "Core/Input.h"
#include "Render/Renderer.h"
#include "Util/Util.h"

BossEnemy::BossEnemy() : super("I", Vector2(Engine::Get().GetWidth()/2, Engine::Get().GetHeight()/2 ), Color::Red)
{
	sortingOrder = 8;

	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;
	attacking = false;
}

BossEnemy::~BossEnemy()
{
}


void BossEnemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (boomCount <=0 || !attacking)
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
	
	UpdateBoomCountUI();

}

void BossEnemy::StartAttack()
{
	attacking = true;
	SetboomCount(-1);

	static Vector2 offsets[] = {
		{0,0}, { 0, -4 }, {4, -2}, {-4, -2}, // 상, 하, 우, 좌
		
		{-4, -4}, {4, -4}, {-4, 0}, {4, 0} // 대각선 4방향
	};

	int randomIndex = Util::Random(0, 8); // 0~7 사이의 인덱스
	Vector2 finalPos = this->GetPosition() + offsets[randomIndex];

	//GetOwner()->AddNewActor(new Effect(finalPos, this, 1.f));

	BossLevel* level = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	level->AddMissile(new guidedMissile(Vector2(GetPosition().x+ 2,GetPosition().y), this));

	UpdateBoomCountUI();
	if (GetboomCount() <= 0)
		attacking = false;
}

void BossEnemy::UpdateBoomCountUI()
{
	BossLevel* currentLevel = dynamic_cast<BossLevel*>(Engine::Get().GetMainLevel());
	currentLevel->boomCount = std::to_string(boomCount);
}

void BossEnemy::MisileAttack()
{
	GetOwner()->AddNewActor(new Effect(this->GetPosition(), this, 1.f));
}
