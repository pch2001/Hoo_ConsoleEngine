#pragma once

#include "Actor/Actor.h"
#include "Util/EngineTimer.h"

using namespace Wanted;

class BossEnemy : public Actor
{
	RTTI_DECLARATIONS(BossEnemy, Actor)

public :
	BossEnemy();
	~BossEnemy();

	void MisileAttack();

	virtual void Tick(float deltaTime) override;
	virtual void OnOverlap(Actor* actor) override;

private :
	EngineTimer attackTimer;



};

