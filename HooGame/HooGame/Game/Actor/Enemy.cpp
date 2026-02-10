#include "Enemy.h"
#include "Engine/Engine.h"
#include "Physics/Physics.h"
#include "PlayerAttack.h"
#include "Level/GameLevel.h"
#include "Render/Renderer.h"
#include "Effect/Effect.h"

#include <iostream>


Enemy::Enemy(const Vector2& position): super("E", position, Color::Red)
{
	sortingOrder = 5;


	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;


	auto* physics = Engine::Get().GetPhysics();

	if (physics != nullptr)
	{
		physics->StartGravity(this);
	}

}

Enemy::~Enemy()
{
}

void Enemy::EnemyAttack()
{
	isAttacking = true;
	GetOwner()->AddNewActor(new Effect(this->GetPosition(), this , 1.f));
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (isAttacking) {
		Vector2 effectPos = { position.x, position.y - 1 }; // ¸Ó¸® À§
		Renderer::Get().Submit("!", effectPos, Color::Red);
		return;
	}

	if (attackCooldown > 0 && !isAttacking) {
		attackCooldown -= deltaTime;
		return;
	}
	

	Level* currentLevel = GetOwner();
	if (!currentLevel) return;

	Actor* target = currentLevel->GetPlayer();

	if (target)
	{
		int diffX = std::abs(position.x - target->GetPosition().x);
		int diffY = std::abs(position.y - target->GetPosition().y);

		if (diffX <= attackRange && diffY <= attackRange)
		{
			EnemyAttack();
			attackCooldown = 3.0f;
		}

	}

	
}

void Enemy::OnOverlap(Actor* actor)
{
	if (actor->IsTypeOf<PlayerAttack>())
	{
		Destroy();
	}
}

void Enemy::OnCheck(int distnace)
{
}

Enemy::Enemy() : super("E", Vector2::Zero, Color::Red)
{
	sortingOrder = 5;

	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = Engine::Get().GetHeight() - 2;


	SetPosition(Vector2(xPosition + 5, yPosition - 10));


	myLayer = CollisionLayer::Enemy;
	targetLayer = CollisionLayer::Player;


	auto* physics = Engine::Get().GetPhysics();

	if (physics != nullptr)
	{
		physics->StartGravity(this);
	}

}
