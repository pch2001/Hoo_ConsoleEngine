#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class Enemy : public Actor
{
	RTTI_DECLARATIONS(Enemy, Actor);

public :
	Enemy();
	Enemy(const Vector2& position);

	void EnemyAttack();


	virtual void Tick(float deltaTime) override;

	virtual void OnOverlap(Actor* actor) override;

	virtual void OnCheck(int distnace) override;

	void SetisAttacking(bool ing) { isAttacking = ing; }

private :
	EngineTimer timer{0.5};

	float attackCooldown = 0.0f; // 공격 쿨타임 
	int attackRange = 3;    // 감지 범위
	bool isAttacking = false;
};

